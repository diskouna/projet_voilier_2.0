#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

typedef struct {
		TIM_TypeDef *Timer;  // TIM1 à TIM4
		unsigned short ARR;
		unsigned short PSC;
} MyTimer_Struct_TypeDef;


void     MyTimer_Base_Init(MyTimer_Struct_TypeDef *Timer);
void MyTimer_Base_Init_ms(TIM_TypeDef *Timer, int period_ms /* period_ms : 1ms -- 21.000ms */);
void MyTimer_Base_Init_us(TIM_TypeDef *Timer, int period_us /*period_us : 1us --- 910us */);
	
#define  MyTimer_Base_Start(Timer) (Timer)->CR1 |= TIM_CR1_CEN
#define  MyTimer_Base_Stop(Timer)  (Timer)->CR1 &= ~TIM_CR1_CEN

/* Timer Interruption */
void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void (*IT_function) (void));
void TIM1_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);

/* PWM Functions */
void MyTimer_PWM(TIM_TypeDef *Timer, char Channel);
void MyTimer_PWM_set_DUTY(TIM_TypeDef *Timer, char Channel, float Duty_Cycle /*percentage*/);
void MyTimer_PWM_start(TIM_TypeDef *Timer, char Channel);
void MyTimer_PWM_stop(TIM_TypeDef *Timer, char Channel);

#endif // MYTIMER_H

