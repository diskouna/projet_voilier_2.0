#ifndef __MY_ADC__
#define __MY_ADC__

#include "stm32f10x.h"
#include <stdint.h>

void My_ADC_Init();
//choose sample rate ?

void MyADC_Power_On(ADC_TypeDef *ADC, char Channel);
void MyADC_Power_Off(ADC_TypeDef *ADC);
int16_t MyADC_Convert(ADC_TypeDef *ADC, char Channel);
	
#endif //__MY_ADC__
