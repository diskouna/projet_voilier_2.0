#include <stddef.h>
#include "MyUSART.h"
#include "MyGPIO.h"


/* TIM4_IRQHandler uses USART TX */

/* Disable IRQs that may pre-empt the Transmission routine MyUSART_Transmit_Safe */
#define 	MY_USART_TX_LOCK()    do {                                  \
																		NVIC_DisableIRQ(TIM4_IRQn);       \
																}	while (0)

#define   MY_USART_TX_UNLOCK()  do {                                 \
																		NVIC_EnableIRQ(TIM4_IRQn);       \
																}	while (0)

																
#define MyUSART_Delay() 	do {                                              \
															for (volatile int i = 0; i < 1000000; ++i)    \
																	__asm {	                                  \
																			nop;                                  \
															};                                            \
													} while(0)

/*
	USART in Asynchronous mode
	  USART  |  TX   |  RX 
      1    |  PA9  | PA10
      2    |  PA2  | PA3
   	  3    |  PB10 | PB11

*/

static void (*MyUSART_Receive_Action[3])(signed char) = {NULL};

void MyUSART_Init(USART_TypeDef *USART, USART_baud_rate_t baud)
{
	/* On active l'horloge de l'USART (Peripheral Clock Enable : page 92 STM32 RM0008 Ref)
	 * On configure les pins TX/RX de l'USART
	 */
		if (USART == USART1) {
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  //PCLK2  = 72MHz
			MyGPIO_Init(GPIOA,  9, AltOut_Ppull);
			MyGPIO_Init(GPIOA, 10, In_PullUp);
		}
		if (USART == USART2) {
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN; //PCLK1 = 36 MHz
			MyGPIO_Init(GPIOA, 2, AltOut_Ppull);
			MyGPIO_Init(GPIOA, 3, In_PullUp);
		}
		if (USART == USART3) {
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN; //PCLK1 = 36MHz
			MyGPIO_Init(GPIOB, 10, AltOut_Ppull);
			MyGPIO_Init(GPIOA, 11, In_PullUp);
		}
		
		USART->CR1 |= USART_CR1_UE;             //On active l'USART
		
		/*On configure le baud  rate*/
		switch(baud) {
			default     : /* Falltrough */
			case B_9600 :
				USART->BRR  |= (USART == USART1) ? ((468 << 4) |(12)) : ((234 << 4) | (6));
				break;
			case B_19200:
				USART->BRR  |= (USART == USART1) ? ((234 << 4) | (6)) : ((117 << 4) | (3));
				break;
			case B_38400:
				//only accurate for USART1
				USART->BRR  |= (USART == USART1) ? ((117 << 4) | (3)) : (( 58 << 4) | (9));
				break;
		}
		
		USART->CR1 |= USART_CR1_TE; //Transmitter enable
		USART->CR1 |= USART_CR1_RE; //Receiver    enable
}


void MyUSART_Destroy(USART_TypeDef *USART)
{
	USART->CR1 &= ~USART_CR1_TE;
	USART->CR1 &= ~USART_CR1_RE;
}

// or write it in an interrupt handle with the highest priority
// use fifo ?

void MyUSART_Transmit(USART_TypeDef *USART, char *msg)
{

	int len = 0;
	
	/*msg is a Null terminated string*/
	while (*msg && len++ < MAX_FRAME_LENGTH) {
		USART->DR  = *msg++;
	  while (!(USART->SR & USART_SR_TC));
	}
	MyUSART_Delay();
}


void MyUSART_Transmit_Safe(USART_TypeDef *USART, char *msg)
{
	MY_USART_TX_LOCK();
	MyUSART_Transmit(USART, msg);
	MY_USART_TX_UNLOCK();
}

void MyUSART_Transmit_IT(USART_TypeDef *USART, char *msg)
{
	;
}

char MyUSART_Receive(USART_TypeDef *USART)
{
	while(!(USART->SR & USART_SR_RXNE));
	return (char)(USART->DR & 0xFF);
}

void	MyUSART_Active_RX_IT(USART_TypeDef *USART, char prio , void (*MyUSART_Receive_Action_par)(signed char))
{
	USART->CR1 |= USART_CR1_RXNEIE;
	if (USART == USART1) {
		MyUSART_Receive_Action[0] = MyUSART_Receive_Action_par;
	
		NVIC_SetPriority(USART1_IRQn, prio); 
		NVIC_EnableIRQ(USART1_IRQn);
	}
	if (USART == USART2) {
		MyUSART_Receive_Action[1] = MyUSART_Receive_Action_par;
	
		NVIC_SetPriority(USART2_IRQn, prio); 
		NVIC_EnableIRQ(USART2_IRQn);
	}
	if (USART == USART3) {
		MyUSART_Receive_Action[2] = MyUSART_Receive_Action_par;
	
		NVIC_SetPriority(USART3_IRQn, prio); 
		NVIC_EnableIRQ(USART3_IRQn);
	}
}

void USART1_IRQHandler(void)
{
	if (USART1->SR & USART_SR_RXNE) {
		//The interruption is cleared by a read to DR register
		signed char vitesse = (USART1->DR & 0xFF); 
		if (MyUSART_Receive_Action[0] != NULL)
			MyUSART_Receive_Action[0](vitesse);
	}
}

void USART2_IRQHandler(void)
{
	if (USART2->SR & USART_SR_RXNE) {
		//The interruption is cleared by a read to DR register
		signed char vitesse = (USART2->DR & 0xFF); 
		if (MyUSART_Receive_Action[1] != NULL)
			MyUSART_Receive_Action[1](vitesse);
	}
}

void USART3_IRQHandler(void)
{
	if (USART3->SR & USART_SR_RXNE) {
		//The interruption is cleared by a read to DR register
		signed char vitesse = (USART3->DR & 0xFF); 
		if (MyUSART_Receive_Action[2] != NULL)
			MyUSART_Receive_Action[2](vitesse);
	}
}

