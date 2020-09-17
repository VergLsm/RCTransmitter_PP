#include "lcd.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "adc.h"
#include "gd32f1x0.h"
#include "rc.h"
#include "variant.h"

void gpio_init() {
    /* enable the gpio clock */
    rcu_periph_clock_enable(GPIO_CLK_LCD_CS1 | GPIO_CLK_LCD_CS2 |
                            GPIO_CLK_LCD_DC | GPIO_CLK_LCD_SCK |
                            GPIO_CLK_LCD_SDA);
    /* configure gpio GPIO port */
    gpio_mode_set(GPIO_POR_LCD_CS1, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                  GPIO_PIN_LCD_CS1);
    gpio_output_options_set(GPIO_POR_LCD_CS1, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_LCD_CS1);
    gpio_mode_set(GPIO_POR_LCD_CS2, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                  GPIO_PIN_LCD_CS2);
    gpio_output_options_set(GPIO_POR_LCD_CS2, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_LCD_CS2);
    gpio_mode_set(GPIO_POR_LCD_DC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                  GPIO_PIN_LCD_DC);
    gpio_output_options_set(GPIO_POR_LCD_DC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_LCD_DC);
    gpio_mode_set(GPIO_POR_LCD_SCK, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                  GPIO_PIN_LCD_SCK);
    gpio_output_options_set(GPIO_POR_LCD_SCK, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_LCD_SCK);
    gpio_mode_set(GPIO_POR_LCD_SDA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                  GPIO_PIN_LCD_SDA);
    gpio_output_options_set(GPIO_POR_LCD_SDA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
                            GPIO_PIN_LCD_SDA);
    SPI_CS2_1;
    SPI_CS_1;
}

void lcd_init(void) {
    gpio_init();

    LCD_init();
    // LCD_full();
    LCD_clear();

    // Picture_display(0, 0, 128, 64, picture_tab);
    // delay(500);
    // Picture_ReverseDisplay(0, 0, 128, 64, picture_tab);
    // delay(500);
    // LCD_clear();

    // draw_chan
    Picture_display(output_chan_x, 5, 6, 16, chan);
    Picture_display(output_chan_x + 6 + 2, 5, 6, 16, chan);
    draw_chan(4, rc_channel_data[4]);
    draw_chan(5, rc_channel_data[5]);

    // draw_battery
    Picture_display(battery_x, 0, 4, 8, battery_start);
    Picture_display(battery_x + 4 + 12, 0, 2, 8, battery_end);

    // draw_uptime
    char str[9];
    strcpy(str, "00:00:00");
    display_str_ascii(uptime_x, 1, font_8X16_bold, 8, str);

    // draw_packet_loss_rate
    display_one_char(packet_loss_rate_x + 16, 1, font_8X16_bold, '%');
}

void lcd_proc(void) {
    static size_t status = 0;
    uint16_t voltage = adc_value[6] * 3 * 330 / 4095;  //放大100倍
    display_voltage(voltage);
    draw_battery((voltage / 2.8) - 200);
    if (status) {
        status = 0;
    } else {
        status = 1;
        // display_str_word(0, 2, hanzi1_GB2312);
        display_str_word(0, 3, hanzi2_GB2312);
        display_str_word(0, 5, hello);
    }
}

void u_itoa(size_t val, char* str, size_t size) {
    char tmp[10];
    itoa(val, str, 10);
    size_t len = size - strlen(str);
    for (size_t i = 0; i < len; i++) {
        tmp[i] = '0';
    }
    strcpy(tmp + len, str);
    strcpy(str, tmp);
}

void display_voltage(uint16_t val) {
    char str[7];
    u_itoa(val, str, 3);
    strcat(str, "V");
    for (size_t i = 0; i < 4; i++) {
        str[6 - i] = str[5 - i];
    }
    str[1] = '.';
    display_str_ascii(79, 0, font_5X7, 5, str);

    // u_itoa(adc_value[4], str, 4);
    // display_str_ascii(6, 1, font_5X7, 4, str);
    // u_itoa(adc_value[5], str, 4);
    // display_str_ascii(6, 2, font_5X7, 4, str);
    u_itoa(rc_channel_data[2], str, 4);
    display_str_ascii(output_chan_x - 20 - 1, 5, font_5X7, 4, str);
    u_itoa(rc_channel_data[3], str, 4);
    display_str_ascii(output_chan_x - 20 - 1, 6, font_5X7, 4, str);
    u_itoa(rc_channel_data[1], str, 4);
    display_str_ascii(output_chan_x + 6 + 2 + 6 + 1, 5, font_5X7, 4, str);
    u_itoa(rc_channel_data[0], str, 4);
    display_str_ascii(output_chan_x + 6 + 2 + 6 + 1, 6, font_5X7, 4, str);
}

// val: 电池百分比
void draw_battery(uint8_t val) {
    val = val / 8;
    uint8_t battery_mid[12];
    for (size_t i = 0; i < 12; i++) {
        if ((12 - i) <= val) {
            battery_mid[i] = 0x5d;
        } else {
            battery_mid[i] = 0x41;
        }
    }
    Picture_display(battery_x + 4, 0, 12, 8, battery_mid);
}

void draw_chan(uint8_t chan, uint16_t val) {
    size_t chan_x;
    if (4 == chan) {
        chan_x = output_chan_x + 1;
    } else if (5 == chan) {
        chan_x = output_chan_x + 6 + 2 + 1;
    } else {
        return;
    }
    if (1000 == val) {
        Picture_display(chan_x, 5, 4, 16, low);
    } else if (1500 == val) {
        Picture_display(chan_x, 5, 4, 16, mid);
    } else if (2000 == val) {
        Picture_display(chan_x, 5, 4, 16, high);
    }
}

void draw_uptime(uint32_t uptime) {
    char str[3];
    // 时
    u_itoa(uptime / 3600, str, 2);
    display_str_ascii(uptime_x, 1, font_8X16_bold, 2, str);
    // 分
    u_itoa(uptime % 3600 / 60, str, 2);
    display_str_ascii(uptime_x + 8 + 8 + 8, 1, font_8X16_bold, 2, str);
    // 秒
    u_itoa(uptime % 60, str, 2);
    display_str_ascii(uptime_x + +8 + 8 + 8 + 8 + 8 + 8, 1, font_8X16_bold, 2,
                      str);
}

void draw_packet_loss_rate(uint8_t plr) {
    char str[3];
    u_itoa(plr, str, 2);
    display_str_ascii(packet_loss_rate_x, 1, font_8X16_bold, 2, str);
}