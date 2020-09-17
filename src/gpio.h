#ifndef GPIO_H
#define GPIO_H

#ifdef cplusplus
 extern "C" {
#endif

#define rc_led_on        rc_gpio_reset
#define rc_led_off       rc_gpio_set
#define rc_led_toggle    rc_gpio_toggle
#define rc_led_g_enable  rc_gpio_reset
#define rc_led_g_disable rc_gpio_set

typedef enum 
{
    RC_LED_1 = 0, // 上面板，右边
    RC_LED_2,     // 上面板，左边
    RC_LED_3,     // 上面板，中间
    RC_LED_A_EN_R, // 上面板红灯
    RC_LED_A_EN_B, // 上面板蓝灯
    RC_LED_LCD,    // LCD背光灯
    RC_PPM,
    RC_POWER,
    RC_BT_VDD,
    RC_BT_EN,
} gpio_typedef_enum;

/* configures led GPIO */
void rc_gpio_init          (gpio_typedef_enum gpionum);
void rc_gpio_reset         (gpio_typedef_enum gpionum);
void rc_gpio_set           (gpio_typedef_enum gpionum);
void rc_gpio_toggle        (gpio_typedef_enum gpionum);

void rc_led_init(void);

#ifdef cplusplus
}
#endif

#endif /* GPIO_H */