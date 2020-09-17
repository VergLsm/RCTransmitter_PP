#ifndef __RADIO_H
#define __RADIO_H

#include <stdint.h>

void rc_radio_init(void);
void rc_radio_enable(void);
void rc_radio_disable(void);
void rc_radio_tx(void);
void proc_radio(void);
uint8_t nrf_status(void);

#endif // __RADIO_H