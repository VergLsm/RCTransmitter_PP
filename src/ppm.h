#ifndef PPM_H
#define PPM_H

#ifdef cplusplus
extern "C"
{
#endif

#include <stdint.h>

extern const uint8_t RC_ADC_PPM_CHANNEL_MAP[];
// 摇杆对应通道，ADC_CH_1 代表ADC第1通道，后面1表示PPM 1通道
#define ADC_CH_0 3 // 航向
#define ADC_CH_1 2 // 油门
#define ADC_CH_2 0 // 副翼
#define ADC_CH_3 1 // 升降
#define ADC_CH_4 4
#define ADC_CH_5 5

void rc_ppm_init(void);
void rc_ppm_enable(void);
void rc_ppm_disable(void);
void rc_ppm_update(void);

#ifdef cplusplus
}
#endif

#endif /* PPM_H */