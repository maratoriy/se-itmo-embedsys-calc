#ifndef SDK_UART_H
#define SDK_UART_H

#include "main.h"

void USART_transmit(uint8_t data[]);
HAL_StatusTypeDef USART_receive(uint8_t *data, uint8_t len);

#endif
