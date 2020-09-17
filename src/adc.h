#ifndef ADC_H
#define ADC_H

#ifdef cplusplus
extern "C"
{
#endif

#include <stdint.h>

extern uint16_t adc_value[];
enum
{
    ADC_CHANNEL_LENGTH = 7,
    ADC_BUFF_SIZE = ADC_CHANNEL_LENGTH,
};

void rc_adc_init();

#ifdef cplusplus
}
#endif

#endif /* ADC_H */