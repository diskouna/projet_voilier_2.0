#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"



void MyADC_Init(ADC_TypeDef * ADC);
void MyADC_Config(ADC_TypeDef * ADC, char voie);
int MyADC_convert_single(ADC_TypeDef * ADC);
void MyADC_Triggerext(ADC_TypeDef * ADC, char event);
void MyADC_ActiveIT(ADC_TypeDef * ADC,char Prio,void(*IT_function)(void));
void ADC1_2_IRQHandler(void);



#define MyADC_Base_Start(ADC) (ADC->CR2 |= ADC_CR2_ADON)
#define MyADC_Base_Stop(ADC) (ADC->CR2 &= ~(0x1))



#define Timer_1_CC1_event 0x0 
#define Timer_1_CC2_event 0x1 
#define Timer_1_CC3_event 0x2 
#define Timer_2_CC2_event 0x3 
#define Timer_3_TRGO_event 0x4 
#define Timer_4_CC4_event 0x5 
#define Timer_8_TRGO_event 0x6 
#define SWSTART_event 0x7



#endif
