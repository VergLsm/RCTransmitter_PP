#ifndef __NRF_H
#define __NRF_H

#include <stdint.h>

//Define the commands for operate the nRF24L01P
#define NRF_READ_REG     0x00  // Command for read register
#define NRF_WRITE_REG    0x20 	// Command for write register
#define NRF_ACTIVATE     0x50
#define RD_RX_PLOAD     0x61  // Command for read Rx payload
#define WR_TX_PLOAD     0xA0  // Command for write Tx payload
#define FLUSH_TX        0xE1 	// Command for flush Tx FIFO
#define FLUSH_RX        0xE2  // Command for flush Rx FIFO
#define REUSE_TX_PL     0xE3  // Command for reuse Tx payload
// #define NOP             0xFF  // Reserve


//Define the register address for nRF24L01P
#define NRF_REGADD_CONFIG            0x00  //  Configurate the status of transceiver, mode of CRC and the replay of transceiver status
#define NRF_REGADD_EN_AA             0x01  //  Enable the atuo-ack in all channels
#define NRF_REGADD_EN_RXADDR         0x02  //  Enable Rx Address
#define NRF_REGADD_SETUP_AW          0x03  // Configurate the address width
#define NRF_REGADD_SETUP_RETR        0x04  //  setup the retransmit
#define NRF_REGADD_RF_CH             0x05  // Configurate the RF frequency
#define NRF_REGADD_RF_SETUP          0x06  // Setup the rate of data, and transmit power
#define NRF_REGADD_STATUS            0x07  //
#define NRF_REGADD_OBSERVE_TX        0x08  //
#define NRF_REGADD_CD                0x09  // Carrier detect
#define NRF_REGADD_RX_ADDR_P0        0x0A  // Receive address of channel 0
#define NRF_REGADD_RX_ADDR_P1        0x0B  // Receive address of channel 1
#define NRF_REGADD_RX_ADDR_P2        0x0C  // Receive address of channel 2
#define NRF_REGADD_RX_ADDR_P3        0x0D  // Receive address of channel 3
#define NRF_REGADD_RX_ADDR_P4        0x0E  // Receive address of channel 4
#define NRF_REGADD_RX_ADDR_P5        0x0F  // Receive address of channel 5
#define NRF_REGADD_TX_ADDR           0x10  //       Transmit address
#define NRF_REGADD_RX_PW_P0          0x11  //  Size of receive data in channel 0
#define NRF_REGADD_RX_PW_P1          0x12  //  Size of receive data in channel 1
#define NRF_REGADD_RX_PW_P2          0x13  //  Size of receive data in channel 2
#define NRF_REGADD_RX_PW_P3          0x14  //  Size of receive data in channel 3
#define NRF_REGADD_RX_PW_P4          0x15  // Size of receive data in channel 4
#define NRF_REGADD_RX_PW_P5          0x16  //  Size of receive data in channel 5
#define NRF_REGADD_FIFO_STATUS       0x17  // FIFO Status
#define NRF_REGADD_DYNPD             0x1C  // Enable dynamic payload length
#define NRF_REGADD_FEATURE           0x1D  // Feature Register

// Register: CONFIG(0x00)
#define MASK_RX_DR				0x40
#define MASK_TX_DS				0x20
#define MASK_MAX_RT				0x10
#define MASK_EN_CRC				0x08
#define MASK_CRCO				0x04
#define MASK_PWR_UP				0x02
#define MASK_PRIM_RX			0x01

// Register: EN_AA(0x01)
#define MASK_ENAA_P5			0x20
#define MASK_ENAA_P4			0x10
#define MASK_ENAA_P3			0x08
#define MASK_ENAA_P2			0x04
#define MASK_ENAA_P1			0x02
#define MASK_ENAA_P0			0x01
#define MASK_ENAA_ALL			0x3F

// Register: EN_RXADDR(0x02)
#define MASK_ERX_P5				0x20
#define MASK_ERX_P4				0x10
#define MASK_ERX_P3				0x08
#define MASK_ERX_P2				0x04
#define MASK_ERX_P1				0x02
#define MASK_ERX_P0				0x01

// Register: SETUP_AW(0x03)
#define MASK_AW_3_BYTES			0x01
#define MASK_AW_4_BYTES			0x02
#define MASK_AW_5_BYTES			0x03

// Register: SETUP_RETR(0x04)
#define MASK_ARD				0xF0
#define MASK_ARC				0x0F

// Register: RF_CH(0x05)
#define MASK_RF_CH				0x7F

// Register: RF_SETUP(0x06)
#define MASK_RF_DR_LOW			0x20
#define MASK_RF_DR_HIGH			0x08
#define MASK_RF_PWR				0x06
#define MASK_RF_LNA_HCURR		0x01

//#define MASK_RF_PWR_18dBm		0x00 // RF output power: -18dBm
//#define MASK_RF_PWR_12dBm		0x02 // RF output power: -12dBm
//#define MASK_RF_PWR_6dBm		0x04 // RF output power: -6dBm
#define MASK_RF_PWR_0dBm		0x06 // RF output power: 0dBm

// Register: STATUS(0x07)
// #define MASK_RX_DR				0x40
// #define MASK_TX_DS				0x20
// #define MASK_MAX_RT				0x10
#define MASK_RX_P_NO			0x0E
#define MASK_STATUS_TX_FULL 	0x01

// Register: OBSERVE_TX(0x08)
#define MASK_PLOS_CNT			0xF0 // Count lost packets
#define MASK_ARC_CNT			0x0F // Count retransmitted packets

// Register: CD(0x09)
#define MASK_CD					0x01 // Carrier Detect

// Register: FIFO_STATUS(0x17)
#define MASK_FIFO_TX_REUSE		0x40
#define MASK_FIFO_TX_FULL 		0x20
#define MASK_FIFO_TX_EMPTY		0x10
#define MASK_FIFO_RX_FULL		0x02
#define MASK_FIFO_RX_EMPTY		0x01

// Register: DYNPD(0x1C)
#define MASK_DPL_P5				0x20
#define MASK_DPL_P4				0x10
#define MASK_DPL_P3				0x08
#define MASK_DPL_P2				0x04
#define MASK_DPL_P1				0x02
#define MASK_DPL_P0				0x01

// Register: FEATURE(0x1D)
#define MASK_EN_DPL				0x04
#define MASK_EN_ACK_PAY			0x02
#define MASK_EN_DYN_ACK			0x01

void nrf_init(void);
uint8_t NRF_Write_Reg(uint8_t res, uint8_t value);
uint8_t NRF_Read_Reg(uint8_t res);
uint8_t NRF_Read_Buf(uint8_t res, uint8_t len, uint8_t *pBuf);
uint8_t NRF_Write_Buf(uint8_t res, uint8_t len, uint8_t *pBuf);

#endif // __NRF_H