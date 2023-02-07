

#ifndef UART_H_
#define UART_H_

#include "stm32l476xx.h"
#include <stdint.h>
void ledon(void);
void ledoff(void);
void led_init(void);
void uart2_rxtx_init(void);
char uart2_read(void);

#endif /* UART_H_ */
