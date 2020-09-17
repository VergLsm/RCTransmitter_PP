#include <stddef.h>

#include "adc.h"
#include "gpio.h"
#include "key.h"
#include "lcd.h"
#include "ppm.h"
#include "rc.h"
#include "systick.h"
#include "variant.h"

typedef enum {
    RC_SYS_BOOTING = 0,
    RC_SYS_RUNING,
    RC_SYS_SHUTDOWNING,
} sys_typedef_enum;

struct {
    uint8_t key[9];
    uint8_t sysStatus;
} counter_proc;

void proc_adc(void) {
    for (size_t i = 0; i < ADC_BUFF_SIZE; i++) {
        switch (i) {  // 摇杆通道，384y = 125x+320000
            case 0:
            case 1:
            case 2:
            case 3: {
                if (adc_value[i] <= 512) {
                    rc_channel_data[RC_ADC_PPM_CHANNEL_MAP[i]] = 1000;
                    continue;
                } else if (adc_value[i] >= 3586) {
                    rc_channel_data[RC_ADC_PPM_CHANNEL_MAP[i]] = 2000;
                    continue;
                }
                rc_channel_data[RC_ADC_PPM_CHANNEL_MAP[i]] =
                    (adc_value[i] * 125 + 320000) / 384;
            } break;
            case 4:
            case 5: {  // 按钮通道 3060-3070  2050-2070 1000-1009 0-9
                if (4000 < adc_value[i]) {  // 放开，无按下
                    for (size_t j = 0, index; j < 4; j++) {
                        index = 4 * i - 16 + j;
                        counter_proc.key[index] = 0;
                    }
                }
                size_t index;
                if (3040 < adc_value[i] && adc_value[i] < 3090) {  // key4-8
                    index = i * 4 - 16 + 3;
                } else if (2040 < adc_value[i] &&
                           adc_value[i] < 2070) {  // key3-7
                    index = i * 4 - 16 + 2;
                } else if (0 < adc_value[i] && adc_value[i] < 9) {  // key1-5
                    index = i * 4 - 16 + 0;
                } else if (980 < adc_value[i] &&
                           adc_value[i] < 1020) {  // key2-6
                    index = i * 4 - 16 + 1;
                } else {
                    continue;
                }
                if (counter_proc.key[index] < 3 &&
                    (!(key_act & (1 << index)))) {
                    counter_proc.key[index]++;
                    if (counter_proc.key[index] == 3) {  // 20ms * 3 = 60ms
                        key_act |= 1 << index;
                        // counter_proc.key[index] = 0;
                    }
                }
            } break;
            case 6: {  // 电池电量
            } break;
            default:
                break;
        }
    }
}

void proc_key_power(void) {
    if (SET == gd_eval_key_state_get(KEY_POWER)) {  // 按下
        if (counter_proc.sysStatus == RC_SYS_RUNING) {
            counter_proc.sysStatus = RC_SYS_SHUTDOWNING;
        }

        if (counter_proc.sysStatus == RC_SYS_SHUTDOWNING) {
            counter_proc.key[8]++;

            if (counter_proc.key[8] >= 50)  // 20ms * 50 = 1s
            {                               // 关机
                rc_led_g_disable(RC_LED_A_EN_B);
                rc_led_g_disable(RC_LED_A_EN_R);
                rc_gpio_reset(RC_POWER);
                LCD_clear();
                while (1) {
                }
            }
        }
    } else {  // 放开
        if (counter_proc.sysStatus == RC_SYS_SHUTDOWNING) {
            counter_proc.sysStatus = RC_SYS_RUNING;
            counter_proc.key[8] = 0;
            rc_led_toggle(RC_LED_LCD);
        }

        if (counter_proc.sysStatus == RC_SYS_BOOTING) {
            counter_proc.sysStatus = RC_SYS_RUNING;
        }
    }
}