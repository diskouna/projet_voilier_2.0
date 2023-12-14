#include "MyServo.h"

void MyServo_Init(void) 
{
	MyTimer_Base_Init_ms(TIM1, 20);     //Periode T = 20ms
	MyTimer_PWM(TIM1, 1);
	MyTimer_PWM_set_DUTY(TIM1, 1, 5.0); //Th = 1ms;
	
	MyTimer_Base_Start(TIM1);
	MyTimer_PWM_start(TIM1, 1);
}

void MyServo_Rotate(unsigned char  angle_deg)
{
	if (angle_deg > 90) angle_deg = 90; 
	angle_deg = 90 - angle_deg;
	float duty_cycle = 5.0f;
	/*
	  Th = 1ms : DC = 5% --> 0°
	  Th = 2ms : DC = 10% --> 90° 
	*/
	duty_cycle += 5.0 * angle_deg / 90.0 ;
	MyTimer_PWM_set_DUTY(TIM1, 1, duty_cycle);
}
