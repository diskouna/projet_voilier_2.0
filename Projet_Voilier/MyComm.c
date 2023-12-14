#include "MyComm.h"

static MyComm_Receive_Action_t MyComm_Receive_Action = NULL;
static MyComm_Get_Frame_t MyComm_Get_Frame           = NULL;
static char MyComm_Frame[MAX_FRAME_LENGTH];

void MyComm_Init(MyComm_Get_Frame_t get_frame, MyComm_Receive_Action_t receive_action)
{
	MyComm_Get_Frame      = get_frame;
	MyComm_Receive_Action = receive_action;
	
	MyUSART_Init(USART1, B_9600);
	
	/* On configugre un TIMER pour l'envoi périodique de frame */
	MyTimer_Base_Init_ms(TIM4, 3000); //period = 3s
	MyTimer_ActiveIT(TIM4, 5, MyComm_Callback_TX);
	MyTimer_Base_Start(TIM4);
	
	/* On configure une interruption  pour gerer la reception sur Rx = PA10 */
	MyUSART_Active_RX_IT(USART1, 2, MyComm_Receive_Action);
}

void MyComm_Callback_TX(void)
{
	if (MyComm_Get_Frame != NULL)
		MyComm_Get_Frame(MyComm_Frame);
	MyUSART_Transmit(USART1, MyComm_Frame);
}

void MyComm_Transmit(char *MSG)
{
	MyUSART_Transmit_Safe(USART1, MSG);
}