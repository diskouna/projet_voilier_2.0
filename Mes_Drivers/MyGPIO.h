#ifndef MYGPIO_H
#define MYGPIO_H

#include "stm32f10x.h"

/* INPUT AND OUTPUT MODE */
//							               CNF  MODE	

#define In_Floating  0x04  // 0b 01  00
#define In_PullDown  0x08  // 0b 10  00
#define In_PullUp    0x08  // 0b 10  00
#define In_Analog    0x00  // 0b 00  00

// Output mode, max speed 2 MHz 
// TODO : max speed 10, 50 MHz
#define Out_Ppull    0x02  // 0b 00  10
#define Out_OD       0x06  // 0b 01  10
#define AltOut_Ppull 0x0A  // 0b 10  10
#define AltOut_OD    0x0E  // 0b 11  10

void MyGPIO_Init  (GPIO_TypeDef *GPIO, char GPIO_Pin, char GPIO_Conf);
int  MyGPIO_Read  (GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Set   (GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Reset (GPIO_TypeDef *GPIO, char GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin);

#endif
