#include "adc.h"
#include "gd32f1x0.h"
#include "systick.h"
#include "variant.h"

#define TIMER TIMER2
#define TIMER_CLK RCU_TIMER2

uint16_t adc_value[ADC_BUFF_SIZE];

static void adc_config(void)
{
    /* ADC channel length config */
    adc_channel_length_config(ADC_REGULAR_CHANNEL,ADC_CHANNEL_LENGTH);
    /* ADC regular channel config */
    adc_regular_channel_config(0,RC_ACD_CHANNEL_VR1,ADC_SAMPLETIME_239POINT5);
    adc_regular_channel_config(1,RC_ACD_CHANNEL_VR2,ADC_SAMPLETIME_239POINT5);
    adc_regular_channel_config(2,RC_ACD_CHANNEL_VR3,ADC_SAMPLETIME_239POINT5);
    adc_regular_channel_config(3,RC_ACD_CHANNEL_VR4,ADC_SAMPLETIME_239POINT5);
    adc_regular_channel_config(4,RC_ACD_CHANNEL_KEY1_4,ADC_SAMPLETIME_239POINT5);
    adc_regular_channel_config(5,RC_ACD_CHANNEL_KEY5_8,ADC_SAMPLETIME_239POINT5);
    adc_regular_channel_config(6,RC_ACD_CHANNEL_BATTERY,ADC_SAMPLETIME_239POINT5);
    /* ADC external trigger enable */
    adc_external_trigger_config(ADC_REGULAR_CHANNEL,ENABLE);
    /* ADC external trigger source config */
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL,ADC_EXTTRIG_REGULAR_T2_TRGO);
    /* ADC data alignment config */
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
    /* enable ADC interface */
    adc_enable();
    /* ADC calibration and reset calibration */
    adc_calibration_enable();
    /* ADC DMA function enable */
    adc_dma_mode_enable();
    /* ADC contineous function enable */
    adc_special_function_config(ADC_SCAN_MODE,ENABLE);
    // adc_special_function_config(ADC_CONTINUOUS_MODE,ENABLE);
    /* ADC software trigger enable */
    // adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
}

static void rcu_config(void)
{
    /* enable GPIOC clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    /* enable DMA clock */
    rcu_periph_clock_enable(RCU_DMA);
    /* enable timer1 clock */
    rcu_periph_clock_enable(TIMER_CLK);
    /* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC);
    /* config ADC clock */
    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV8);
}

static void gpio_config(void)
{
    /* config the GPIO as analog mode */
    gpio_mode_set(GPIO_PORT_ADC_VR1, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_ADC_VR1);
    gpio_mode_set(GPIO_PORT_ADC_VR2, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_ADC_VR2);
    gpio_mode_set(GPIO_PORT_ADC_VR3, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_ADC_VR3);
    gpio_mode_set(GPIO_PORT_ADC_VR4, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_ADC_VR4);
    gpio_mode_set(GPIO_PORT_ADC_KEY1_4, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_ADC_KEY1_4);
    gpio_mode_set(GPIO_PORT_ADC_KEY5_8, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_ADC_KEY5_8);
    gpio_mode_set(GPIO_PORT_ADC_BATTERY, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_ADC_BATTERY);
}

static void dma_config(void)
{
    /* ADC_DMA_channel configuration */
    dma_deinit(DMA_CH0);
    dma_periph_address_config(DMA_CH0,(uint32_t)(&ADC_RDATA));
    dma_memory_address_config(DMA_CH0,(uint32_t)(&adc_value));
    dma_transfer_direction_config(DMA_CH0,DMA_PERIPHERAL_TO_MEMORY);
    dma_memory_width_config(DMA_CH0,DMA_MEMORY_WIDTH_16BIT);
    dma_periph_width_config(DMA_CH0,DMA_PERIPHERAL_WIDTH_16BIT);
    dma_priority_config(DMA_CH0,DMA_PRIORITY_MEDIUM);
    dma_transfer_number_config(DMA_CH0,ADC_BUFF_SIZE);
    dma_periph_increase_disable(DMA_CH0);
    dma_memory_increase_enable(DMA_CH0);
    dma_circulation_enable(DMA_CH0);
    dma_channel_enable(DMA_CH0);
    dma_interrupt_enable(DMA_CH0, DMA_INT_FTF);
}

static void timer_config(void)
{
    timer_deinit(TIMER);
    timer_prescaler_config(TIMER, 1200-1, TIMER_PSC_RELOAD_UPDATE);
    timer_autoreload_value_config(TIMER, 1200-1);
    timer_master_output_trigger_source_select(TIMER, TIMER_TRI_OUT_SRC_UPDATE);
    timer_enable(TIMER);
}

void rc_adc_init()
{
    /* system clocks configuration */
    rcu_config();
    /* GPIO configuration */
    gpio_config();
    /* DMA configuration */
    dma_config();
    /* TIMER configuration */
    timer_config();
    /* ADC configuration */
    adc_config();
}