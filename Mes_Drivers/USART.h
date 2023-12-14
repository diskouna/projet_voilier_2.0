#ifndef USART_H
#define USART_H

#include "stm32f10x.h"

void Configure_USART(USART_TypeDef * USART); 
void Send(USART_TypeDef * USART, char data);

#endif
