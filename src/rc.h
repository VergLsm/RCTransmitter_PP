#ifndef RC_H
#define RC_H

#ifdef cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <gd32f1x0.h>
#include "gd32f1x0_libopt.h"
#include "variant.h"

enum {
    RC_CHANNEL_LENGTH = 6,
    RC_PPM_ORGINAL_DATA_LENGTH = (RC_CHANNEL_LENGTH + 1) * 2,
};

#define nrf_ce_low() (GPIO_BC(GPIO_POR_BK) = GPOI_PIN_BK_CE)
#define nrf_ce_high() (GPIO_BOP(GPIO_POR_BK) = GPOI_PIN_BK_CE)
#define spi_cs_low() (GPIO_BC(GPIO_POR_BK) = GPOI_PIN_BK_CS)
#define spi_cs_high() (GPIO_BOP(GPIO_POR_BK) = GPOI_PIN_BK_CS)
#define spi_sck_low() (GPIO_BC(GPIO_POR_BK) = GPOI_PIN_BK_SCK)
#define spi_sck_high() (GPIO_BOP(GPIO_POR_BK) = GPOI_PIN_BK_SCK)
#define spi_mosi_low() (GPIO_BC(GPIO_POR_BK) = GPOI_PIN_BK_MOSI)
#define spi_mosi_high() (GPIO_BOP(GPIO_POR_BK) = GPOI_PIN_BK_MOSI)
#define spi_miso_read() (GPIO_ISTAT(GPIO_POR_BK) & (GPOI_PIN_BK_MISO))
#define spi_miso_high() __asm__ volatile("nop")
#define nrf_irq_high() __asm__ volatile("nop")

extern uint16_t rc_channel_data[];
extern uint16_t ppm_orginal_data[];

typedef enum { OUTPUT_RADIO = 0x1, OUTPUT_PPM = 0x2 } output_enum;

struct {
    output_enum output;
    uint32_t uptime;
    uint8_t recedPacket;
} sys_status;

void rc_init(void);

#ifdef cplusplus
}
#endif

#endif /* RC_H */