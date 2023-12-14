#include <stdlib.h>
#include <inttypes.h> 
#include "MyTimer.h"
#include "MyGPIO.h"


void MyTimer_Base_Init( MyTimer_Struct_TypeDef *Timer)
{
	// On active l'horloge du Timer
	switch ((uintptr_t)Timer->Timer) 
	{
		case (uintptr_t)TIM1 : 
			// TIM1 utilise l'arbre d'horloge APB2
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			break;
		// Les autres Timers utilisent APB1 
		case (uintptr_t)TIM2 : 
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			break;
		case (uintptr_t)TIM3 : 
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			break;
		case (uintptr_t)TIM4 : 
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			break;
	}
	// On configure les registres :
  //  -ARR (AUTO-RELOAD)
	//  -PSC (PRESCALER)
	Timer ->Timer ->ARR = Timer ->ARR;
	Timer ->Timer ->PSC = Timer ->PSC;
}

void MyTimer_Base_Init_ms(TIM_TypeDef *Timer, int period_ms )
{
		if (period_ms <    1) period_ms =    1;
		if (period_ms > 21000) period_ms = 21000;
	
		MyTimer_Base_Init( &(MyTimer_Struct_TypeDef) {
												.Timer = Timer,
												.ARR   = 24000 - 1,   //On veut le plus grand ARR possible
												.PSC   = 3 * period_ms - 1 
											});
}

void MyTimer_Base_Init_us(TIM_TypeDef *Timer, int period_us)
{
	if (period_us <    1) period_us =    1;
	if (period_us > 900) period_us = 900;
		
	MyTimer_Base_Init( &(MyTimer_Struct_TypeDef) {
												.Timer = Timer,
												.ARR   = 72 * period_us - 1,
												.PSC   = 1 - 1
											});
}

// Tableau de pointeurs sur fonction utilisé pour : 
// - "enregistrer" les handlers des IRQs dans  @MyTimer_ActiveIT() et
// - executer ces derniers dans @TIMX_IRQHandler

static void (*glob_func_ptr[4]) (void) = {0};

/*
Les fonctions TIMX_IRQHandler() "surchargent celles définies 
dans le fichier "startup_stm32f10x_md.s
*/
void TIM1_UP_IRQHandler(void)
{
	TIM1->SR &= ~TIM_SR_UIF;	 // On rabaisse le flag d'interruption
	if (glob_func_ptr[0] != NULL) 
		glob_func_ptr[0]() ;     // On exécute la fonction définie par l'utilisateur
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;	 // On rabaisse le flag d'interruption
	if (glob_func_ptr[1] != NULL) 
		glob_func_ptr[1]() ;     // On exécute la fonction définie par l'utilisateur
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;	 // On rabaisse le flag d'interruption
	if (glob_func_ptr[2] != NULL) 
		glob_func_ptr[2]() ;     // On exécute la fonction définie par l'utilisateur
}

void TIM4_IRQHandler(void)
{
	TIM4->SR &= ~TIM_SR_UIF;	 // On rabaisse le flag d'interruption
	if (glob_func_ptr[3] != NULL) 
		glob_func_ptr[3]() ;     // On exécute la fonction définie par l'utilisateur
}

void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void (*IT_function) (void)) 
{ 
	//On active l'interruption (update interrupt) au niveau du Timer
	Timer->DIER |= TIM_DIER_UIE;
	
	//On active l'interruption au niveau du NVIC et 
	//on définit la fonction HANDLER 
	switch ((uintptr_t)Timer) 
	{
		case (uintptr_t)TIM1 : 
			// TIM1 : only "Update Interrupt" is supported
			NVIC_EnableIRQ(TIM1_UP_IRQn);
			NVIC_SetPriority(TIM1_UP_IRQn, Prio);
			glob_func_ptr[0] = IT_function;
			break;
		case (uintptr_t)TIM2 : 
			NVIC_EnableIRQ(TIM2_IRQn);
			NVIC_SetPriority(TIM2_IRQn, Prio);
			glob_func_ptr[1] = IT_function;
			break;
		case (uintptr_t)TIM3 : 
			NVIC_EnableIRQ(TIM3_IRQn);
			NVIC_SetPriority(TIM3_IRQn, Prio);
			glob_func_ptr[2] = IT_function;
			break;
		case (uintptr_t)TIM4 : 
			NVIC_EnableIRQ(TIM4_IRQn);
			NVIC_SetPriority(TIM4_IRQn, Prio);
			glob_func_ptr[3] = IT_function;
			break;
	}
}

//
// Pulse Width Modulation : PWM 
//
void MyTimer_PWM(TIM_TypeDef *Timer, char Channel)
{
	if (1 <= Channel && Channel <= 4) {
		uint32_t global_CCMR = (Timer->CCMR2 << 16) | (Timer->CCMR1);
		char Config = (0x06 << 4 | 0x01 << 3);
		
		global_CCMR &= ~(Config << (Channel - 1) * 8);
		global_CCMR |=  (Config << (Channel - 1) * 8);
		
		Timer->CCMR1 = (global_CCMR >> 0 * 16) & 0xFFFF;
		Timer->CCMR2 = (global_CCMR >> 1 * 16) & 0xFFFF;
		
		/*On configure le GPIO/AFIO correspondant*/
		
		switch((uintptr_t)Timer) {
			case (uintptr_t)TIM1 :
					switch (Channel) {
						case 1: case 2: case 3: case 4:
							MyGPIO_Init(GPIOA, (char)(Channel + 7), AltOut_Ppull);
							break;
						default:
							break;
					}
					break;
			case (uintptr_t)TIM2 :
				switch (Channel) {
						case 1: case 2: case 3: case 4:
							MyGPIO_Init(GPIOA, (char)(Channel - 1), AltOut_Ppull);
							break;
						default:
							break;
					}
				break;
			case (uintptr_t)TIM3 :
				switch (Channel) {
						case 1: case 2:
							MyGPIO_Init(GPIOA, (char)(Channel + 5), AltOut_Ppull);
							break;
						case 3: case 4:
							MyGPIO_Init(GPIOB, (char)(Channel - 3), AltOut_Ppull);
							break;
						default:
							break;
					}
				break;
			case (uintptr_t)TIM4 :
				switch (Channel) {
						case 1: case 2: case 3: case 4:
							MyGPIO_Init(GPIOB, (char)(Channel + 5), AltOut_Ppull);
							break;
						default:
							break;
					}
				break;
			default :
				break;
		}
	}
}

//make it more sensitive : Duty_cycle --> float  
void MyTimer_PWM_set_DUTY(TIM_TypeDef *Timer, char Channel, float Duty_Cycle)
{		
	if (Duty_Cycle <   0.0f) Duty_Cycle = 0.0f;
	if (Duty_Cycle > 100.0f) Duty_Cycle = 0.0f;
	
	uint16_t new_CRR = (uint16_t)(Duty_Cycle * Timer->ARR / 100);
	switch (Channel) {
		case 1:
			Timer->CCR1 = new_CRR;
			break;
		case 2:
			Timer->CCR2 = new_CRR;
			break;
		case 3:
			Timer->CCR3 = new_CRR;
			break;
		case 4:
			Timer->CCR4 = new_CRR;
			break;
		default:
				break;
	}	
}

void MyTimer_PWM_start(TIM_TypeDef *Timer, char Channel)
{
	if (1 <= Channel && Channel <= 4) {
		Timer->CCER |= (0x01 << 4 * (Channel - 1));
		// Configuration particulière pour TIM1
		if (Timer == TIM1) Timer->BDTR |= TIM_BDTR_MOE;
	}
}

void MyTimer_PWM_stop(TIM_TypeDef *Timer, char Channel)
{
	if (1 <= Channel && Channel <= 4)  
		Timer->CCER &= ~(0x01 << 4 * (Channel - 1));
		// Configuration particulière pour TIM1
		if (Timer == TIM1) Timer->BDTR &= ~TIM_BDTR_MOE;
}

//
//Input Capture Mode
//
