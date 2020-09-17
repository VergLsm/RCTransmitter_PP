#include "uart.h"
#include "variant.h"

#include <string.h>

static rcu_periph_enum COM_CLK[] = {RC_COM1_CLK,
                                    RC_COM2_CLK};

static uint32_t COM_TX_PIN[] = {RC_COM1_TX_PIN,
                                RC_COM2_TX_PIN};

static uint32_t COM_RX_PIN[] = {RC_COM1_RX_PIN,
                                RC_COM2_RX_PIN};

static uint32_t RC_COM_TX_GPIO_PORT[] = {RC_COM1_TX_GPIO_PORT,
                                         RC_COM2_TX_GPIO_PORT};

static uint32_t RC_COM_RX_GPIO_PORT[] = {RC_COM1_RX_GPIO_PORT,
                                         RC_COM2_RX_GPIO_PORT};

static uint32_t RC_COM_TX_GPIO_CLK[] = {RC_COM1_TX_GPIO_CLK,
                                        RC_COM2_TX_GPIO_CLK};

static uint32_t RC_COM_RX_GPIO_CLK[] = {RC_COM1_RX_GPIO_CLK,
                                        RC_COM2_RX_GPIO_CLK};

static uint32_t RC_COM_AF[] = {RC_COM1_AF,
                               RC_COM2_AF};

static uint32_t RC_COM_BAUDRATE[] = {RC_COM1_BAUDRATE,
                                     RC_COM2_BAUDRATE};

void com_init(uint32_t COM)
{
    uint32_t COM_ID = 0U;
    if (RC_COM1 == COM)
    {
        COM_ID = 0U;
    }
    if (RC_COM2 == COM)
    {
        COM_ID = 1U;
    }

    /* enable GPIO clock */
    rcu_periph_clock_enable(RC_COM_TX_GPIO_CLK[COM_ID]);
    rcu_periph_clock_enable(RC_COM_RX_GPIO_CLK[COM_ID]);

    /* enable USART clock */
    rcu_periph_clock_enable(COM_CLK[COM_ID]);

    /* connect port to USARTx_Tx */
    gpio_af_set(RC_COM_TX_GPIO_PORT[COM_ID], RC_COM_AF[COM_ID], COM_TX_PIN[COM_ID]);

    /* connect port to USARTx_Rx */
    gpio_af_set(RC_COM_RX_GPIO_PORT[COM_ID], RC_COM_AF[COM_ID], COM_RX_PIN[COM_ID]);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(RC_COM_TX_GPIO_PORT[COM_ID], GPIO_MODE_AF, GPIO_PUPD_PULLUP, COM_TX_PIN[COM_ID]);
    gpio_output_options_set(RC_COM_TX_GPIO_PORT[COM_ID], GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, COM_TX_PIN[COM_ID]);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(RC_COM_RX_GPIO_PORT[COM_ID], GPIO_MODE_AF, GPIO_PUPD_PULLUP, COM_RX_PIN[COM_ID]);
    gpio_output_options_set(RC_COM_RX_GPIO_PORT[COM_ID], GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, COM_RX_PIN[COM_ID]);

    /* USART configure */
    usart_deinit(COM);
    usart_baudrate_set(COM, RC_COM_BAUDRATE[COM_ID]);
    usart_transmit_config(COM, USART_TRANSMIT_ENABLE);
    usart_receive_config(COM, USART_RECEIVE_ENABLE);
    usart_enable(COM);
}

void rc_com_init(void)
{
    com_init(RC_COM1);
    com_init(RC_COM2);
}

void print_str(const char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        usart_data_transmit(RC_COM1, str[i]);
        //wait for transmission buffer empty (TBE) before sending next data
        while (RESET == usart_flag_get(RC_COM1, USART_FLAG_TBE))
        {
        }
    }
}