#ifndef UART_H
#define UART_H

#ifdef cplusplus
 extern "C" {
#endif

#include "gd32f1x0.h"

void rc_com_init();

void print_str(const char* str);

#ifdef cplusplus
}
#endif

#endif /* UART_H */