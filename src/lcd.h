#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gd32f1x0.h>
#include <stdint.h>
#include <stddef.h>

#include "gd32f1x0_libopt.h"
#include "variant.h"

#define RC  // 标识，用来动态设置对比度

#define SPI_SDA_0 (GPIO_BC(GPIO_POR_LCD_SDA) = GPIO_PIN_LCD_SDA)   // SDA接口
#define SPI_SDA_1 (GPIO_BOP(GPIO_POR_LCD_SDA) = GPIO_PIN_LCD_SDA)  //置位
#define SPI_SCK_0 (GPIO_BC(GPIO_POR_LCD_SCK) = GPIO_PIN_LCD_SCK)   // sck接口
#define SPI_SCK_1 (GPIO_BOP(GPIO_POR_LCD_SCK) = GPIO_PIN_LCD_SCK)
#define SPI_DC_0 (GPIO_BC(GPIO_POR_LCD_DC) = GPIO_PIN_LCD_DC)  // DC接口
#define SPI_DC_1 (GPIO_BOP(GPIO_POR_LCD_DC) = GPIO_PIN_LCD_DC)
#define SPI_CS_0 (GPIO_BC(GPIO_POR_LCD_CS1) = GPIO_PIN_LCD_CS1)  // CS1接口
#define SPI_CS_1 (GPIO_BOP(GPIO_POR_LCD_CS1) = GPIO_PIN_LCD_CS1)
#define SPI_CS2_0 (GPIO_BC(GPIO_POR_LCD_CS2) = GPIO_PIN_LCD_CS2)  // CS2接口
#define SPI_CS2_1 (GPIO_BOP(GPIO_POR_LCD_CS2) = GPIO_PIN_LCD_CS2)
#define SPI_FSO (GPIO_ISTAT(GPIO_POR_LCD_SO) & GPIO_PIN_LCD_SO)

#ifdef AF_SDA
// PF7 7*2=14
#define SET_SDA_OUT                                           \
    GPIO_CTL(GPIO_POR_LCD_SDA) =                              \
        (GPIO_CTL(GPIO_POR_LCD_SDA) & (~(0x03 << 14))) | 0x01 \
                                                             << 14  //推挽输出
#define SET_SDA_IN                                            \
    GPIO_CTL(GPIO_POR_LCD_SDA) =                              \
        (GPIO_CTL(GPIO_POR_LCD_SDA) & (~(0x03 << 14))) | 0x00 \
                                                             << 14  //浮空输入
#endif

extern const unsigned char picture_tab[];
extern const uint8_t battery_start[];
extern const uint8_t battery_end[];
extern const unsigned char hello[];
extern const unsigned char hanzi1_GB2312[];
extern const unsigned char hanzi2_GB2312[];
extern const uint8_t signal[];
extern const uint8_t nosignal[];
extern const uint8_t ppm[];
extern const uint8_t noppm[];
extern const uint8_t chan[];
extern const uint8_t high[];
extern const uint8_t mid[];
extern const uint8_t low[];

typedef enum {
    font_5X7,       // 5X7点阵ASCII标准字符
    font_7X8,       // 7X8点阵ASCII标准字符
    font_8X16,       // 8X16点阵ASCII标准字符
    font_8X16_bold,  // 8X16点阵ASCII粗体字符
} fontType;

void LCD_init(void);
void LCD_clear(void);
void display_str_word(unsigned char X_ADD, unsigned char Y_ADD,
                      const unsigned char *chinese_str);
size_t display_one_char(unsigned char X_ADD, unsigned char Y_ADD, fontType ft,
                      char achar);
void display_str_ascii(unsigned char X_ADD, unsigned char Y_ADD, fontType ft,
                       uint8_t length, const char *str);
void Picture_display(uint8_t x, uint8_t y, uint8_t width, uint8_t height,
                     const unsigned char *ptr_pic);
void Picture_ReverseDisplay(uint8_t x, uint8_t y, uint8_t width, uint8_t height,
                            const unsigned char *ptr_pic);

void lcd_init(void);
void lcd_proc(void);
void display_voltage(uint16_t val);
void draw_battery(uint8_t);
void draw_chan(uint8_t chan, uint16_t val);
void draw_uptime(uint32_t uptime);
void draw_packet_loss_rate(uint8_t plr);

#define output_chan_x 88
#define output_ppm_x 6
#define output_signal_x output_ppm_x + 8 + 1
#define battery_x 105
#define uptime_x 59
#define packet_loss_rate_x 28

#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */
