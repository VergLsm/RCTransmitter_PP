#include "radio.h"

#include "gd32f1x0.h"
#ifdef RCT_LCD
#include "lcd.h"
#endif
#include "nrf.h"
#include "rc.h"
#include "variant.h"

void nrf_rx_mode(void) {
    nrf_ce_low();
    NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_CONFIG,
                  MASK_RX_DR | MASK_TX_DS | MASK_MAX_RT | MASK_EN_CRC |
                      MASK_CRCO | MASK_PWR_UP | MASK_PRIM_RX);
    NRF_Write_Reg(FLUSH_RX, 0);
    nrf_ce_high();
}

void nrf_tx_mode() {
    nrf_ce_low();
    NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_CONFIG,
                  MASK_RX_DR | MASK_TX_DS | MASK_MAX_RT | MASK_EN_CRC |
                      MASK_CRCO | MASK_PWR_UP);
    NRF_Write_Reg(FLUSH_TX, 0);
    nrf_ce_high();
}

void rc_radio_init(void) {
    /* enable the gpio clock */
    rcu_periph_clock_enable(GPIO_CLK_BK);
    /* configure gpio GPIO port */
    gpio_mode_set(
        GPIO_POR_BK, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
        GPOI_PIN_BK_SCK | GPOI_PIN_BK_CS | GPOI_PIN_BK_CE | GPOI_PIN_BK_MOSI);
    gpio_output_options_set(
        GPIO_POR_BK, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
        GPOI_PIN_BK_SCK | GPOI_PIN_BK_CS | GPOI_PIN_BK_CE | GPOI_PIN_BK_MOSI);
    // MISO
    gpio_mode_set(GPIO_POR_BK, GPIO_MODE_INPUT, GPIO_PUPD_NONE,
                  GPOI_PIN_BK_MISO);

    nrf_init();

    NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_EN_AA, 0x00);
    NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_EN_RXADDR, MASK_ERX_P0);
    NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_SETUP_AW, MASK_AW_3_BYTES);
    // NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_SETUP_RETR, 0x36);  //
    NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_RF_CH, 120);
    NRF_Write_Reg(
        NRF_WRITE_REG + NRF_REGADD_RF_SETUP,
        MASK_RF_DR_LOW | MASK_RF_PWR_0dBm | MASK_RF_LNA_HCURR);  // 1mbps
    NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_STATUS,
                  MASK_RX_DR | MASK_TX_DS | MASK_MAX_RT);  //
    // NRF_Write_Buf(NRF_REGADD_RX_ADDR_P0, 3, );
    // NRF_Write_Buf(NRF_REGADD_TX_ADDR, 3, );
    NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_RX_PW_P0, 12);
}

uint8_t nrf_status(void) {
    uint8_t status = NRF_Read_Reg(NRF_READ_REG + NRF_REGADD_STATUS);
    return status;
}

void rc_radio_enable(void) {
    nrf_tx_mode();
#ifdef RCT_LCD
    Picture_display(output_signal_x, 0, 9, 8, signal);
#endif
}
void rc_radio_disable(void) {
    nrf_ce_low();
    NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_CONFIG,
                  MASK_RX_DR | MASK_TX_DS | MASK_MAX_RT | MASK_EN_CRC);
#ifdef RCT_LCD
    Picture_display(output_signal_x, 0, 9, 8, nosignal);
#endif
}

void rc_radio_tx(void) {
    nrf_tx_mode();
    NRF_Write_Buf(WR_TX_PLOAD, 12, (uint8_t*)rc_channel_data);
}

void proc_radio(void) {
    uint8_t status = NRF_Read_Reg(NRF_READ_REG + NRF_REGADD_STATUS);
    if (status & MASK_TX_DS) {
        NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_STATUS, MASK_TX_DS);
        nrf_rx_mode();
    }
    if (status & MASK_RX_DR) {
        NRF_Write_Reg(NRF_WRITE_REG + NRF_REGADD_STATUS, MASK_RX_DR);
        NRF_Write_Reg(FLUSH_RX, 0);
        nrf_ce_low();
        sys_status.recedPacket++;
    }
}