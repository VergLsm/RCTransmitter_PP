#include "gpio.h"

#include "gd32f1x0.h"
#include "variant.h"

/* private variables */
static uint32_t GPIO_PORT[] = {
    GPIO_POR_LED_1,      GPIO_POR_LED_2,   GPIO_POR_LED_3, GPIO_POR_LED_A_EN_R,
    GPIO_POR_LED_A_EN_B, GPIO_POR_LED_LCD, GPIO_POR_PPM,   GPIO_POR_POWER,
    GPIO_POR_BT_VDD,     GPIO_POR_BT_EN,
};

static uint32_t GPIO_PIN[] = {
    GPIO_PIN_LED_1,      GPIO_PIN_LED_2,   GPIO_PIN_LED_3, GPIO_PIN_LED_A_EN_R,
    GPIO_PIN_LED_A_EN_B, GPIO_PIN_LED_LCD, GPIO_PIN_PPM,   GPIO_PIN_POWER,
    GPIO_PIN_BT_VDD,     GPIO_PIN_BT_EN,
};

static rcu_periph_enum GPIO_CLK[] = {
    GPIO_CLK_LED_1,      GPIO_CLK_LED_2,   GPIO_CLK_LED_3, GPIO_CLK_LED_A_EN_R,
    GPIO_CLK_LED_A_EN_B, GPIO_CLK_LED_LCD, GPIO_CLK_PPM,   GPIO_CLK_POWER,
    GPIO_CLK_BT_VDD,     GPIO_CLK_BT_EN,
};

void rc_gpio_init(gpio_typedef_enum gpionum) {
    /* enable the gpio clock */
    rcu_periph_clock_enable(GPIO_CLK[gpionum]);
    /* configure gpio GPIO port */
    gpio_mode_set(GPIO_PORT[gpionum], GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                  GPIO_PIN[gpionum]);
    gpio_output_options_set(GPIO_PORT[gpionum], GPIO_OTYPE_PP,
                            GPIO_OSPEED_50MHZ, GPIO_PIN[gpionum]);

    // GPIO_BC(GPIO_PORT[gpionum]) = GPIO_PIN[gpionum];
}

void rc_gpio_reset(gpio_typedef_enum gpionum) {
    GPIO_BC(GPIO_PORT[gpionum]) = GPIO_PIN[gpionum];
}

void rc_gpio_set(gpio_typedef_enum gpionum) {
    GPIO_BOP(GPIO_PORT[gpionum]) = GPIO_PIN[gpionum];
}

void rc_gpio_toggle(gpio_typedef_enum gpionum) {
    GPIO_OCTL(GPIO_PORT[gpionum]) ^= GPIO_PIN[gpionum];
}

void rc_led_init(void) {
    rc_gpio_init(RC_LED_1);
    rc_gpio_init(RC_LED_2);
    rc_gpio_init(RC_LED_3);

    rc_gpio_init(RC_LED_A_EN_B);
    rc_gpio_init(RC_LED_A_EN_R);

    rc_gpio_init(RC_LED_LCD);

    rc_led_off(RC_LED_1);
    rc_led_off(RC_LED_2);
    rc_led_off(RC_LED_3);

    rc_led_g_enable(RC_LED_A_EN_B);
    rc_led_g_disable(RC_LED_A_EN_R);

    rc_led_off(RC_LED_LCD);

    rc_gpio_init(RC_BT_VDD);
    // rc_gpio_init(RC_BT_EN);

    rc_gpio_set(RC_BT_VDD);
    // rc_gpio_set(RC_BT_EN);
}
