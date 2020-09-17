#include "ppm.h"

#include <stddef.h>

#include "gd32f1x0.h"
#include "rc.h"
#include "variant.h"
#include "gpio.h"
#include "lcd.h"

#define TIMER_PPM TIMER15
#define TIMER_PPM_CLK RCU_TIMER15

const uint8_t RC_ADC_PPM_CHANNEL_MAP[] = {ADC_CH_0, ADC_CH_1, ADC_CH_2,
                                          ADC_CH_3, ADC_CH_4, ADC_CH_5};
const uint16_t RC_PPM_INTERVAL = 300;

uint16_t ppm_orginal_data[RC_PPM_ORGINAL_DATA_LENGTH] = {};

static void timer_config(void) {
    /* enable timer15 clock */
    rcu_periph_clock_enable(TIMER_PPM_CLK);

    nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
    nvic_irq_enable(TIMER15_IRQn, 0, 1);

    timer_deinit(TIMER_PPM);
    timer_prescaler_config(TIMER_PPM, 72 - 1, TIMER_PSC_RELOAD_UPDATE);
    timer_autoreload_value_config(TIMER_PPM, 20000 - 1);
    /* TIMER0 update DMA request enable */
    timer_dma_enable(TIMER_PPM, TIMER_DMA_UPD);
    timer_interrupt_flag_clear(TIMER_PPM, TIMER_INT_UP);
    timer_interrupt_enable(TIMER_PPM, TIMER_INT_UP);
    // timer_enable(TIMER_PPM);
}

void TIMER15_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER15, TIMER_INT_FLAG_UP);
    rc_gpio_toggle(RC_PPM);
}

static void dma_config(void) {
    /* enable DMA clock */
    rcu_periph_clock_enable(RCU_DMA);

    /* ADC_DMA_channel configuration */
    dma_deinit(DMA_CH2);
    dma_periph_address_config(DMA_CH2, (uint32_t)(&TIMER_CAR(TIMER_PPM)));
    dma_memory_address_config(DMA_CH2, (uint32_t)(&ppm_orginal_data));
    dma_transfer_direction_config(DMA_CH2, DMA_MEMORY_TO_PERIPHERAL);
    dma_memory_width_config(DMA_CH2, DMA_MEMORY_WIDTH_16BIT);
    dma_periph_width_config(DMA_CH2, DMA_PERIPHERAL_WIDTH_16BIT);
    dma_priority_config(DMA_CH2, DMA_PRIORITY_ULTRA_HIGH);
    dma_transfer_number_config(DMA_CH2, RC_PPM_ORGINAL_DATA_LENGTH);
    dma_periph_increase_disable(DMA_CH2);
    dma_memory_increase_enable(DMA_CH2);
    dma_circulation_enable(DMA_CH2);
    // dma_channel_enable(DMA_CH2);
}

void rc_ppm_init() {
    // PPM orginal data initialization
    for (size_t i = 0; i <= RC_CHANNEL_LENGTH; i++) {
        ppm_orginal_data[i * 2] = RC_PPM_INTERVAL - 1;  // 0,2,4,6,...
    }
    rc_ppm_update();
    /* GPIO configuration */
    rc_gpio_init(RC_PPM);
    // 初始化状态，决定有效电平高低，如果不对，再修改
    rc_gpio_set(RC_PPM);
    /* DMA configuration */
    dma_config();
    /* TIMER configuration */
    timer_config();
}

void rc_ppm_enable() {
    dma_channel_enable(DMA_CH2);
    timer_enable(TIMER_PPM);
    Picture_display(output_ppm_x, 0, 8, 8, ppm);
}

void rc_ppm_disable() {
    dma_channel_disable(DMA_CH2);
    timer_disable(TIMER_PPM);
    Picture_display(output_ppm_x, 0, 8, 8, noppm);
}
 
void rc_ppm_update(void) {
    uint16_t ppm_proc_sum = 0;// 计算ppm最后电平时长用
    for (size_t i = 0; i < RC_CHANNEL_LENGTH; i++) {
        if (2000 < rc_channel_data[i]) rc_channel_data[i] = 2000;
        if (rc_channel_data[i] < 1000) rc_channel_data[i] = 1000;
        ppm_orginal_data[i * 2 + 1] = rc_channel_data[i] - RC_PPM_INTERVAL - 1;
        ppm_proc_sum += rc_channel_data[i];
    }
    ppm_orginal_data[RC_CHANNEL_LENGTH * 2 + 1] =
        20000 - RC_PPM_INTERVAL - ppm_proc_sum - 1;  // 20000-500-sum
}