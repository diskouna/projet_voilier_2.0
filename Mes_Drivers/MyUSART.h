#ifndef MYUSART_H
#define MYUSART_H

#include <stm32f10x.h>

#define MAX_FRAME_LENGTH 4096

typedef enum USART_baud_rate_t {
	B_9600  ,
	B_19200 ,
  B_38400 
} USART_baud_rate_t;

void MyUSART_Init(USART_TypeDef *USART, USART_baud_rate_t baud);
void MyUSART_Transmit(USART_TypeDef *USART, char *DATA);
void MyUSART_Transmit_Safe(USART_TypeDef *USART, char *msg);
char MyUSART_Receive(USART_TypeDef *USART);

void	MyUSART_Active_RX_IT(USART_TypeDef *USART, char prio , 
													   void (*MyUSART_Receive_Action)(signed char)
													);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
														 
#endif //MYUSART_H
