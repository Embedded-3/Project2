#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include <stdint.h>

void uart_init(void);
int uart_available(void);
char uart_read(void);

#endif