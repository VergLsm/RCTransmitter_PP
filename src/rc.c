#include "rc.h"

#include <stdint.h>
#include "radio.h"
#include "gpio.h"
#include "ppm.h"

uint16_t rc_channel_data[RC_CHANNEL_LENGTH] = {1500, 1500, 1000,
                                               1500, 1500, 1500};

void rc_init() {
    sys_status.output = OUTPUT_RADIO;
    rc_radio_enable();
    rc_led_on(RC_LED_1);

    rc_ppm_disable();
    
    rc_led_g_disable(RC_LED_A_EN_B);
    rc_led_g_enable(RC_LED_A_EN_R);
    rc_led_on(RC_LED_3);
}