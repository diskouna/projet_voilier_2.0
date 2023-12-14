#include "MyTimer.h"
#include "MyGPIO.h"
#include "MYADC.h"
#include "GIROUETTE.h"


void EXTI4_IRQHandler (){
	
	EXTI->PR |=EXTI_PR_PR4;
	TIM2->CNT =0x00;
};	

void initialisation_compteur_girouette (){
	MyTimer_Struct_TypeDef myTim;
	
	// on initialise les ports des channels 1 et 2 du Timer 2
		
	MyGPIO_Init  (GPIOA, 0 ,In_Floating);
	MyGPIO_Init  (GPIOA, 1 ,In_Floating);
	
	
  //on initialise le Timer2
	myTim.Timer=TIM2;
	myTim.ARR = 0xffff; //1439;
	myTim.PSC = 0;
	MyTimer_Base_Init(&myTim);
	
	//on assigne TI1 et TI2 à TI1FP1 et TI2FP2
	
	TIM2->CCMR1 &= ~(TIM_CCMR1_CC1S  );
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0  ;
	
	TIM2->CCMR1 &= ~(TIM_CCMR1_CC2S  );
	TIM2->CCMR1 |= TIM_CCMR1_CC2S_0  ;
	
	//on met TIM2 en mode compteur/décompteur

  TIM2->CCER &=~(TIM_CCER_CC1P);
	TIM2->CCER &=~(TIM_CCER_CC2P);
	
  TIM2->SMCR &= ~(TIM_SMCR_SMS);
  TIM2->SMCR |= (0x3);
	
	//on lance le Timer2
	MyTimer_Base_Start(TIM2);
}
	

void initialisation_interuption_girouette () {
	//on initialise le port d'entrée de l'indexe
	MyGPIO_Init  (GPIOC, 4 ,In_Floating);

	//on enable clk AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI4_PC;
	EXTI->FTSR |= EXTI_FTSR_TR4;
	EXTI->SWIER |= EXTI_SWIER_SWIER4;
	EXTI->IMR |= EXTI_IMR_MR4;
	
	//on active l'interuption puis on redéfinit sa priorité dans l'NVIC
	NVIC_SetPriority(EXTI4_IRQn,(uint32_t)0x3);
	NVIC_EnableIRQ(EXTI4_IRQn);
}

	
float get_angle_girouette(){
	 float angle = (float)(TIM2->CNT);
	 if (angle>800) {angle = -(angle-0xFFFF);}	
	 angle = (angle)/4;
	 if (angle<0){angle+=360;}
	 if (angle>180){angle=(angle-360)*-1;}
		return angle ;
}




	



