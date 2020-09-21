#include "key.h"

#include <stddef.h>

#include "gd32f1x0.h"
#include "gpio.h"
#ifdef RCT_LCD
#include "lcd.h"
#endif
#include "ppm.h"
#include "radio.h"
#include "rc.h"
#include "variant.h"

static uint32_t KEY_PORT[] = {KEY_GPIO_PORT_POWER};

static uint32_t KEY_PIN[] = {KEY_PIN_POWER};

static rcu_periph_enum KEY_CLK[] = {KEY_GPIO_CLK_POWER};

static exti_line_enum KEY_EXTI_LINE[] = {KEY_EXTI_LINE_POWER};

static uint8_t KEY_PORT_SOURCE[] = {KEY_EXTI_PORT_SOURCE_POWER};

static uint8_t KEY_PIN_SOURCE[] = {KEY_EXTI_PIN_SOURCE_POWER};

static uint8_t KEY_IRQn[] = {KEY_EXTI_IRQn_POWER};

void gd_eval_key_init(key_typedef_enum keynum, keymode_typedef_enum key_mode) {
    /* enable the key clock */
    rcu_periph_clock_enable(KEY_CLK[keynum]);
    rcu_periph_clock_enable(RCU_CFGCMP);

    /* configure button pin as input */
    gpio_mode_set(KEY_PORT[keynum], GPIO_MODE_INPUT, GPIO_PUPD_NONE,
                  KEY_PIN[keynum]);

    if (key_mode == KEY_MODE_EXTI) {
        /* enable and set key EXTI interrupt to the lowest priority */
        nvic_irq_enable(KEY_IRQn[keynum], 2U, 0U);

        /* connect key EXTI line to key GPIO pin */
        syscfg_exti_line_config(KEY_PORT_SOURCE[keynum],
                                KEY_PIN_SOURCE[keynum]);

        /* configure key EXTI line */
        exti_init(KEY_EXTI_LINE[keynum], EXTI_INTERRUPT, EXTI_TRIG_FALLING);
        exti_interrupt_flag_clear(KEY_EXTI_LINE[keynum]);
    }
}

uint8_t gd_eval_key_state_get(key_typedef_enum keynum) {
    return gpio_input_bit_get(KEY_PORT[keynum], KEY_PIN[keynum]);
}

void rc_keyProc_1() {}
void rc_keyProc_2() {  // 切换输出 ppm / wireless
    if (sys_status.output & OUTPUT_RADIO) {
        rc_led_off(RC_LED_1);
        // 关闭radio
        rc_radio_disable();
        // 灯转成红色
        // rc_led_g_disable(RC_LED_A_EN_B);
        // rc_led_g_enable(RC_LED_A_EN_R);
    } else {
        rc_led_on(RC_LED_1);
        // 打开radio
        rc_radio_enable();
    }
    sys_status.output ^= OUTPUT_RADIO;
}
void rc_keyProc_3() {
    if (1000 < rc_channel_data[5]) {
        rc_channel_data[5] -= 500;
    }
#ifdef RCT_LCD
    draw_chan(5, rc_channel_data[5]);
#endif
}
void rc_keyProc_4() {
    if (rc_channel_data[5] < 2000) {
        rc_channel_data[5] += 500;
    }
#ifdef RCT_LCD
    draw_chan(5, rc_channel_data[5]);
#endif
}
void rc_keyProc_5() {}
void rc_keyProc_6() {
    if (sys_status.output & OUTPUT_PPM) {
        rc_led_off(RC_LED_2);
        // 关闭ppm
        rc_ppm_disable();
        // 灯转成蓝色
        // rc_led_g_disable(RC_LED_A_EN_R);
        // rc_led_g_enable(RC_LED_A_EN_B);
    } else {
        rc_led_on(RC_LED_2);
        // 打开ppm
        rc_ppm_enable();
    }
    sys_status.output ^= OUTPUT_PPM;
}
void rc_keyProc_7() {
    if (rc_channel_data[4] < 2000) {
        rc_channel_data[4] += 500;
    }
#ifdef RCT_LCD
    draw_chan(4, rc_channel_data[4]);
#endif
}
void rc_keyProc_8() {
    if (1000 < rc_channel_data[4]) {
        rc_channel_data[4] -= 500;
    }
#ifdef RCT_LCD
    draw_chan(4, rc_channel_data[4]);
#endif
}

void (*keyProcArr[])(void) = {rc_keyProc_1, rc_keyProc_2, rc_keyProc_3,
                              rc_keyProc_4, rc_keyProc_5, rc_keyProc_6,
                              rc_keyProc_7, rc_keyProc_8};

void rc_key_init(void) { gd_eval_key_init(KEY_POWER, KEY_MODE_GPIO); }

uint8_t key_act;
void proc_key(void) {
    // 按钮按下检测
    for (size_t i = 0; i < 8; i++) {
        if (key_act & (1 << i)) {
            key_act ^= (1 << i);
            keyProcArr[i]();
        }
    }
}
