#include "nrf.h"

#include <stddef.h>
#include <stdint.h>

#include "rc.h"

uint8_t spi_rw(uint8_t data) {
    spi_sck_low();  //先将时钟线拉低
    for (size_t i = 0; i < 8; i++) {
        if ((data & 0x80) == 0x80) {  //从高位发送
            spi_mosi_high();
        } else {
            spi_mosi_low();
        }
        spi_sck_high();  //将时钟线拉高，在时钟上升沿，数据发送到从设备
        data <<= 1;
        if (spi_miso_read()) {  //读取从设备发射的数据
            data |= 0x01;
        }
        spi_sck_low();  //在下降沿数据被读取到主机
    }
    return data;  //返回读取到的数据}
}

/*****************************************************************************
 * 函  数：uint8_t NRF_Write_Reg(uint8_t res,uint8_t value)
 * 功  能：从寄存器写入一字节数据
 * 参  数：res:寄存器地址;value:写入的值
 * 返回值：status:读取的寄存器状态值
 * 备  注：无
 *****************************************************************************/
uint8_t NRF_Write_Reg(uint8_t res, uint8_t value) {
    uint8_t status;

    spi_cs_low();
    status = spi_rw(res);
    spi_rw(value);
    spi_cs_high();

    return status;  //返回寄存器状态值
}

/*****************************************************************************
 * 函  数：uint8_t NRF_Read_Reg(uint8_t res)
 * 功  能：从寄存器读取一字节数据
 * 参  数：res:寄存器地址
 * 返回值：ret:读取的值
 * 备  注：无
 *****************************************************************************/
uint8_t NRF_Read_Reg(uint8_t res) {
    uint8_t ret;

    spi_cs_low();
    spi_rw(res);
    ret = spi_rw(0x00);  //在读取数据前稳定MISO的电平,防止触发slave设备
    spi_cs_high();

    return ret;
}

/*****************************************************************************
 * 函  数：uint8_t NRF_Read_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
 * 功  能：在指定位置读取一定长度的数据
 * 参  数：res:指定位置;len:数据长度;*pBuf:指定数据的首地址
 * 返回值：status:寄存器的状态
 * 备  注：无
 *****************************************************************************/
uint8_t NRF_Read_Buf(uint8_t res, uint8_t len, uint8_t *pBuf) {
    spi_cs_low();
    uint8_t status = spi_rw(res);
    for (size_t i = 0; i < len; i++) {
        pBuf[i] = spi_rw(0x00);
    }
    spi_cs_high();

    return status;
}

/*****************************************************************************
 * 函  数：uint8_t NRF_Write_Buf(uint8_t res,uint8_t len,uint8_t *pBuf)
 * 功  能：在指定位置写入一定长度的数据
 * 参  数：res:指定位置;len:数据长度;*pBuf:指定数据的首地址
 * 返回值：status:寄存器的状态
 * 备  注：无
 *****************************************************************************/
uint8_t NRF_Write_Buf(uint8_t res, uint8_t len, uint8_t *pBuf) {
    spi_cs_low();
    uint8_t status = spi_rw(res);
    for (size_t i = 0; i < len; i++) {
        spi_rw(*pBuf++);
        // spi_rw(pBuf[i]);
    }
    spi_cs_high();

    return status;
}

void nrf_init(void) {
    spi_miso_high();
    nrf_irq_high();
    nrf_ce_low();
    spi_cs_high();
    spi_sck_low();
}
