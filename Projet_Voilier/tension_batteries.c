
#include "MyGPIO.h"
#include "MYADC.h"
#include "TENSION_BATTERIES.h"
#include "MyUSART.h"
#include "MyTimer.h"


void test_tension_batterie() {
	int tension;
	tension = MyADC_convert_single(ADC1);
	if (tension<critical_voltage){ //on vérifie si la tension est inferieur à 20% de la tension max
		MyUSART_Transmit(USART1,message);//si oui on prévient l'utilisateur
	}
}

void init_tension_batterie() {
	MyADC_Init(ADC1);
	MyADC_Config(ADC1, 8);
	MyADC_Triggerext(ADC1,SWSTART_event);
//	MyTimer_Base_Init_ms(TIM4,1000);
//	MyTimer_ActiveIT (TIM4,4,&test_tension_batterie);
//	MyTimer_Base_Start(TIM4);
}
