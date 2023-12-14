#include "USART.h"

void Configure_USART(USART_TypeDef * USART) 
{
	switch ((uintptr_t)USART) 
	{
		case (uintptr_t)USART1 :
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Validation horloge USART
			USART1->CR1 |= USART_CR1_UE;					// Activation de l'USART
			USART1->CR1 &= ~USART_CR1_M;					// Choix d'une taille de 8 bits de données
			USART1->CR2 &= USART_CR2_STOP;				// Choix d'un seul bit de stop
			USART1->BRR |= 468 << 4;
			USART1->BRR |= 75;										// Fix le baud rate à 9600bps
			USART1->CR1 |= USART_CR1_TE;					// Envoi de la première trame d'attente
			break;
		
		case (uintptr_t)USART2 :
			RCC->APB2ENR |= RCC_APB1ENR_USART2EN; // Validation horloge USART
			USART2->CR1 |= USART_CR1_UE;					// Activation de l'USART
			USART2->CR1 &= ~USART_CR1_M;					// Choix d'une taille de 8 bits de données
			USART2->CR2 &= USART_CR2_STOP;				// Choix d'un seul bit de stop
			USART2->BRR |= 468 << 4;
			USART2->BRR |= 75;										// Fix le baud rate à 9600bps
			USART2->CR1 |= USART_CR1_TE;					// Envoi de la première trame d'attente
			break;
		
		case (uintptr_t)USART3 :
			RCC->APB2ENR |= RCC_APB1ENR_USART3EN; // Validation horloge USART
			USART3->CR1 |= USART_CR1_UE;					// Activation de l'USART
			USART3->CR1 &= ~USART_CR1_M;					// Choix d'une taille de 8 bits de données
			USART3->CR2 &= USART_CR2_STOP;				// Choix d'un seul bit de stop
			USART3->BRR |= 468 << 4;
			USART3->BRR |= 75;										// Fix le baud rate à 9600bps
			USART3->CR1 |= USART_CR1_TE;					// Envoi de la première trame d'attente
			break;
	}
}

void Send(USART_TypeDef * USART, char data)
{
	switch ((uintptr_t)USART) 
	{
		case (uintptr_t)USART1 :
			USART1->DR |= data;										// Ecriture de la donnée dans le registre DR
			while(!(USART1->SR & USART_SR_TC)) {}	// Attente de la fin de transmission
			break;
				
		case (uintptr_t)USART2 :
			USART2->DR |= data;										// Ecriture de la donnée dans le registre DR
			while(!(USART2->SR & USART_SR_TC)) {}	// Attente de la fin de transmission
			break;
				
		case (uintptr_t)USART3 :
			USART2->DR |= data;										// Ecriture de la donnée dans le registre DR
			while(!(USART2->SR & USART_SR_TC)) {}	// Attente de la fin de transmission
			break;
	}
}

