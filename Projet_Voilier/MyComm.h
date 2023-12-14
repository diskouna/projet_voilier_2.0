#ifndef MYCOMM_H
#define MYCOMM_H

#include <stm32f10x.h>
#include <stddef.h>
#include "MyUSART.h"
#include "MyTimer.h"

/*
	TIM4 : 3000ms 
	USART1 : 
	PA9  : TX
	PA10 : RX
 */


/*Fonction � appeler quand on re�oit la consigne de vitesse de la T�lecommande*/
typedef void (*MyComm_Receive_Action_t)(signed char vitesse);
/*Fonction � appeler pour obtenir la frame � envoyer*/
typedef void (*MyComm_Get_Frame_t    )(char frame[]);

void MyComm_Init(MyComm_Get_Frame_t get_frame, MyComm_Receive_Action_t receive_action);
/*Handlers  d'interruption*/
void MyComm_Callback_TX(void);

void MyComm_Transmit(char *MSG);

#endif // MYCOMM_H
