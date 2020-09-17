#ifndef VARIANT_H
#define VARIANT_H

#ifdef cplusplus
 extern "C" {
#endif

/* tamper push-button */
#define KEY_PIN_POWER                   GPIO_PIN_12
#define KEY_GPIO_PORT_POWER             GPIOA
#define KEY_GPIO_CLK_POWER              RCU_GPIOA
#define KEY_EXTI_LINE_POWER             EXTI_12
#define KEY_EXTI_PORT_SOURCE_POWER      EXTI_SOURCE_GPIOA
#define KEY_EXTI_PIN_SOURCE_POWER       EXTI_SOURCE_PIN12
#define KEY_EXTI_IRQn_POWER             EXTI4_15_IRQn

#define GPIO_CLK_POWER 			    	RCU_GPIOA
#define GPIO_POR_POWER			    	GPIOA
#define GPIO_PIN_POWER 				    GPIO_PIN_15

// PPM
#define GPIO_CLK_PPM   				    RCU_GPIOF
#define GPIO_POR_PPM 				    GPIOF
#define GPIO_PIN_PPM    			    GPIO_PIN_6

#define GPIO_CLK_BT_VDD   				RCU_GPIOA
#define GPIO_POR_BT_VDD 				GPIOA
#define GPIO_PIN_BT_VDD    				GPIO_PIN_2

#define GPIO_CLK_BT_EN   				RCU_GPIOA
#define GPIO_POR_BT_EN 				    GPIOA
#define GPIO_PIN_BT_EN    				GPIO_PIN_3

// LED
#define GPIO_CLK_LED_A_EN_R 			RCU_GPIOB
#define GPIO_POR_LED_A_EN_R 			GPIOB
#define GPIO_PIN_LED_A_EN_R 			GPIO_PIN_9

#define GPIO_CLK_LED_A_EN_B 			RCU_GPIOB
#define GPIO_POR_LED_A_EN_B 			GPIOB
#define GPIO_PIN_LED_A_EN_B 			GPIO_PIN_8

#define GPIO_CLK_LED_1                  RCU_GPIOC
#define GPIO_POR_LED_1                  GPIOC
#define GPIO_PIN_LED_1                  GPIO_PIN_13

#define GPIO_CLK_LED_2  				RCU_GPIOC
#define GPIO_POR_LED_2  				GPIOC
#define GPIO_PIN_LED_2  				GPIO_PIN_15

#define GPIO_CLK_LED_3  				RCU_GPIOC
#define GPIO_POR_LED_3  				GPIOC
#define GPIO_PIN_LED_3  				GPIO_PIN_14

// LED_LCD
#define GPIO_CLK_LED_LCD                 RCU_GPIOB
#define GPIO_POR_LED_LCD                 GPIOB
#define GPIO_PIN_LED_LCD                 GPIO_PIN_14

// LCD

#define GPIO_CLK_LCD_CS1                 RCU_GPIOB
#define GPIO_POR_LCD_CS1                 GPIOB
#define GPIO_PIN_LCD_CS1                 GPIO_PIN_11

#define GPIO_CLK_LCD_CS2                 RCU_GPIOB
#define GPIO_POR_LCD_CS2                 GPIOB
#define GPIO_PIN_LCD_CS2                 GPIO_PIN_12

#define GPIO_CLK_LCD_DC                 RCU_GPIOB
#define GPIO_POR_LCD_DC                 GPIOB
#define GPIO_PIN_LCD_DC                 GPIO_PIN_13

#define GPIO_CLK_LCD_SCK                RCU_GPIOB
#define GPIO_POR_LCD_SCK                GPIOB
#define GPIO_PIN_LCD_SCK                GPIO_PIN_15

#define GPIO_CLK_LCD_SDA                RCU_GPIOF
#define GPIO_POR_LCD_SDA                GPIOF
#define GPIO_PIN_LCD_SDA                GPIO_PIN_7

#define AF_SDA

#ifndef AF_SDA
#define GPIO_POR_LCD_SO                 GPIOB
#define GPIO_PIN_LCD_SO                 GPIO_Pin_15
#else
// 共用一根数据线
#define GPIO_POR_LCD_SO                 GPIO_POR_LCD_SDA
#define GPIO_PIN_LCD_SO                 GPIO_PIN_LCD_SDA
#endif

/* definition for COM 1, connected to USART0 */
#define RC_COM1                             USART0
#define RC_COM1_CLK                         RCU_USART0
#define RC_COM1_AF                          GPIO_AF_1
#define RC_COM1_BAUDRATE                    115200U
#define RC_COM1_RX_GPIO_PORT                GPIOA
#define RC_COM1_RX_GPIO_CLK                 RCU_GPIOA
#define RC_COM1_RX_PIN                      GPIO_PIN_10
#define RC_COM1_TX_GPIO_PORT                GPIOA
#define RC_COM1_TX_GPIO_CLK                 RCU_GPIOA
#define RC_COM1_TX_PIN                      GPIO_PIN_9
/* definition for COM 2, connected to USART1 */
#define RC_COM2                             USART1
#define RC_COM2_CLK                         RCU_USART1
#define RC_COM2_AF                          GPIO_AF_4
#define RC_COM2_BAUDRATE                    9600U
#define RC_COM2_RX_GPIO_PORT                GPIOB
#define RC_COM2_RX_GPIO_CLK                 RCU_GPIOB
#define RC_COM2_RX_PIN                      GPIO_PIN_0
#define RC_COM2_TX_GPIO_PORT                GPIOA
#define RC_COM2_TX_GPIO_CLK                 RCU_GPIOA
#define RC_COM2_TX_PIN                      GPIO_PIN_8


// ADC
#define GPIO_PORT_ADC_VR1                   GPIOA
#define GPIO_PIN_ADC_VR1                    GPIO_PIN_4
#define RC_ACD_CHANNEL_VR1                  ADC_CHANNEL_4
#define GPIO_PORT_ADC_VR2                   GPIOA
#define GPIO_PIN_ADC_VR2                    GPIO_PIN_5
#define RC_ACD_CHANNEL_VR2                  ADC_CHANNEL_5
#define GPIO_PORT_ADC_VR3                   GPIOB
#define GPIO_PIN_ADC_VR3                    GPIO_PIN_1
#define RC_ACD_CHANNEL_VR3                  ADC_CHANNEL_9
#define GPIO_PORT_ADC_VR4                   GPIOA
#define GPIO_PIN_ADC_VR4                    GPIO_PIN_0
#define RC_ACD_CHANNEL_VR4                  ADC_CHANNEL_0
#define GPIO_PORT_ADC_KEY1_4                GPIOA
#define GPIO_PIN_ADC_KEY1_4                 GPIO_PIN_1
#define RC_ACD_CHANNEL_KEY1_4               ADC_CHANNEL_1
#define GPIO_PORT_ADC_KEY5_8                GPIOA
#define GPIO_PIN_ADC_KEY5_8                 GPIO_PIN_6
#define RC_ACD_CHANNEL_KEY5_8               ADC_CHANNEL_6
#define GPIO_PORT_ADC_BATTERY               GPIOA
#define GPIO_PIN_ADC_BATTERY                GPIO_PIN_7
#define RC_ACD_CHANNEL_BATTERY              ADC_CHANNEL_7

// BK2425
#define GPIO_CLK_BK                         RCU_GPIOB
#define GPIO_POR_BK                         GPIOB
#define GPOI_PIN_BK_SCK                     GPIO_PIN_5
#define GPOI_PIN_BK_CS                      GPIO_PIN_6
#define GPOI_PIN_BK_CE                      GPIO_PIN_7
#define GPOI_PIN_BK_MOSI                    GPIO_PIN_4
#define GPOI_PIN_BK_MISO                    GPIO_PIN_3

#ifdef cplusplus
}
#endif

#endif /* VARIANT_H */