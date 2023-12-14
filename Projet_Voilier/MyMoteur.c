#include "MyMoteur.h"

void MyMoteur_Init(void)
{
	MyTimer_Base_Init_us(TIM3, 50);     //20KHz
	MyTimer_PWM(TIM3, 4);
	MyTimer_PWM_set_DUTY(TIM3, 4, 0.0); 
	
	MyTimer_Base_Start(TIM3);	
	
	MyTimer_PWM_start(TIM3, 4);
	
	MyGPIO_Init(GPIOB, 2, Out_Ppull);
	MyGPIO_Reset(GPIOB, 2);
}

void MyMoteur_Start(char vit_per, MyMoteur_sens_t sens)
{
	if (sens == MyMoteur_ANTI_HORAIRE)
		MyGPIO_Set(GPIOB, 2);
	if (sens == MyMoteur_HORAIRE)
		MyGPIO_Reset(GPIOB, 2);
	
	if (vit_per > 100)  vit_per  = 100;
  
	MyTimer_PWM_set_DUTY(TIM3, 4, vit_per ); // vitesse
}

void MyMoteur_Stop(void)
{
	MyTimer_PWM_stop(TIM3, 4);
	MyGPIO_Reset(GPIOB, 2);
}

