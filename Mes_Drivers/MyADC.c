#ifndef MyADC_H
#define MyADC_H

#include "MyADC.h"

/*Only one channel per ADC unit*/

void MyADC_Power_On(ADC_TypeDef *ADC, char Channel)
{
	// On configure d'abord le prescaler de l'ADCCLK(72MHz -> 12MHz < 14MHz)
	RCC->CFGR &= ~RCC_CFGR_ADCPRE;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	// On active l'horloge sur l'ADC
	if (ADC == ADC1)
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	if (ADC == ADC2)
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	
	ADC->CR2 |= ADC_CR2_ADON; //On démarre l'ADC
/*
	ADC->CR2 |= ADC_CR2_EXTTRIG;
	ADC->CR2 &= ADC_CR2_EXTSEL;
	ADC->CR2 
EXTSEL[2:0]: External event select for regular group
These bits select the external event used to trigger the start of conversion of a regular group:
For ADC1 and ADC2, the assigned triggers are:
000: Timer 1 CC1 event
001: Timer 1 CC2 event
010: Timer 1 CC3 event
011: Timer 2 CC2 event
100: Timer 3 TRGO event
101: Timer 4 CC4 event
110: EXTI line 11/TIM8_TRGO event (TIM8_TRGO is available only in high-density and XLdensity devices)
111: SWSTART
	*/
	ADC->SQR1 &= ADC_SQR1_L;
	ADC->SQR1 |= ((1 - 1) << 20); //Sequence length = 1
	
	if (Channel < 16)
		ADC->SQR3 |= Channel; //First conversion in regular sequence
	
	//Calibration de l'ADC
	ADC->CR2 |= ADC_CR2_CAL;
	// On attend la fin de la calibration (ADC->CR2->CAL passe à 0);
	while (ADC->CR2 & ADC_CR2_CAL); 

}

void MyADC_Power_Off(ADC_TypeDef *ADC)
{
	
}

int16_t MyADC_Convert(ADC_TypeDef *ADC, char Channel)
{
	ADC->CR2 |= ADC_CR2_ADON;
	
	while (!(ADC->SR & ADC_SR_EOC));
	
	ADC->SR &= ~ADC_SR_EOC;
	
	return (ADC->DR & 0xFFF);
}

#endif //MyADC_H