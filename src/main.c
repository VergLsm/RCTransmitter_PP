#include <stddef.h>
#include <stdlib.h>

#include "adc.h"
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "gpio.h"
#include "key.h"
#ifdef RCT_LCD
#include "lcd.h"
#endif
#include "ppm.h"
#include "proc.h"
#include "radio.h"
#include "rc.h"
#include "systick.h"
#include "uart.h"
#include "variant.h"

struct {
    uint8_t output;
} counter_main;

char result[7];  //存放字符输出

void setup() {
    rc_gpio_init(RC_POWER);
    rc_gpio_set(RC_POWER);

    rc_led_init();
    rc_com_init();
    rc_key_init();
    rc_adc_init();
    rc_ppm_init();
    rc_radio_init();
#ifdef RCT_LCD
    lcd_init();
#endif
    rc_init();
}

void loop() {
    // adc 采集转换传输完成 50Hz
    if (dma_interrupt_flag_get(DMA_CH0, DMA_INT_FLAG_FTF)) {
        dma_interrupt_flag_clear(DMA_CH0, DMA_INT_FLAG_FTF);

        proc_adc();
        if (sys_status.output & OUTPUT_PPM) {
            rc_ppm_update();
        }
        if (sys_status.output & OUTPUT_RADIO) {
            rc_radio_tx();
        }

        proc_key_power();

        counter_main.output++;
    }

    proc_key();
    proc_radio();

    if (counter_main.output >= 50)  // 20ms * 50 = 1000ms
    {
        counter_main.output = 0;
        sys_status.uptime++;

#ifdef RCT_LCD        
        draw_uptime(sys_status.uptime);
        // print_str("Test string for UART! \r\n");
        // for (size_t i = 0; i < ADC_BUFF_SIZE; i++) {
        //     if (i == ADC_CHANNEL_LENGTH) {
        //         print_str("\r\n");
        //     }

        //     itoa(adc_value[i], result, 10);
        //     print_str(result);
        //     print_str(" ");
        // }
        itoa(nrf_status(), result, 16);
        // display_str_ascii(25, 0, font_5X7, 2, result);
        // itoa(sys_status.recedPacket, result, 10);
        draw_packet_loss_rate(sys_status.recedPacket);
        sys_status.recedPacket = 0;
        // print_str(result);
        // print_str("\r\n");

        lcd_proc();
#endif

        for (size_t i = 0; i < RC_CHANNEL_LENGTH; i++) {
            itoa(rc_channel_data[i], result, 10);
            print_str(result);
            print_str(" ");
        }
        print_str("\r\n");
        for (size_t i = 0; i < RC_PPM_ORGINAL_DATA_LENGTH; i++) {
            itoa(ppm_orginal_data[i], result, 10);
            print_str(result);
            print_str(" ");
        }
        print_str("\r\n");
    }
}

int main(void) {
    systick_config();
    setup();
    while (1) {
        loop();
    }
    return 0;  // never reached but for safety
}
