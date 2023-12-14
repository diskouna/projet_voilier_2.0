#include "MYADC.h"
#include "MyGPIO.h"
//pointeur de fonction
void (* ptr_fct2_IT)(void);


void MyADC_Init(ADC_TypeDef * ADC){
	
	//1 -- on enable la clock de l'ADC
	if (ADC == ADC1)
	{RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;}
	else if (ADC == ADC2)
	{RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;};
	
	
	//2 -- on divise par 6 la fréquence de la clock d'entrée pour pour être en dessous de 14MHz
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	//3 -- on met ADON à 1
	MyADC_Base_Start(ADC);
	
}
	
void MyADC_Config(ADC_TypeDef * ADC, char voie){
	//on enable la clock du port ou se trouve la voie
	
	MyGPIO_Init  (GPIOB, 0 ,In_Analog);
	//on configure l'ADC
	ADC->SQR1&= ~(0xf<<20);
	ADC->SQR1|= (0x01<<20);// fixe le nombre de conversion à nb_conversions
  ADC->SQR3|= voie; // indique la voie à convertir
  ADC->CR2 |= ADC_CR2_CAL; // début de la calibration
  while ((ADC->CR2 & ADC_CR2_CAL)); // attente de la fin de la calibration

}

int MyADC_convert_single(ADC_TypeDef * ADC){
    ADC->CR2 |= (0x1<<22);
		while(!(ADC->SR & ADC_SR_EOC) ){}; // attente de la fin de conversion
    //ADC->SR &= ~ADC_SR_EOC; // validation de la conversion
    return ADC->DR & ~((0x0F) << 12); // retour de la conversion
}

void MyADC_Triggerext(ADC_TypeDef * ADC,char event){
	ADC->CR2 |= (0x1<<20); // on permet le declenchement par un parametre exterieur
	ADC->CR2 &= ~(0x7<<17);
	ADC->CR2 |= (event<<17);//on choisit l'evenement déclencheur
}

void MyADC_ActiveIT(ADC_TypeDef * ADC,char Prio,void(*IT_function)(void)){
	ADC->CR1 |= (0x01<<5); //1 -- on met EOCIE à 1
	//2 -- on a autorisé le passage de l'interruption correspondant à ADC
	{NVIC_EnableIRQ(ADC1_2_IRQn);
	//3 -- on définie l'ordre de priorité
	NVIC_SetPriority(ADC1_2_IRQn,(uint32_t)Prio);}
	ptr_fct2_IT = IT_function;	
}

void ADC1_2_IRQHandler(void) {

	ptr_fct2_IT();
	
}

