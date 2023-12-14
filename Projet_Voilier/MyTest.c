/**************************************************************
 * @file  MyTest.c
 * @brief Ce fichier source  contient la définition des tests 
 *        unitaire et d'intégration des differents composants 
 *        du voilier
 *
 *************************************************************/
#include "MyTest.h"

/**********************************************************
								TEST DU SERVOMOTEUR
**********************************************************/

static void Callback_Servo(void)
{
	static char angle = 0;
	angle += 5;
	MyServo_Rotate(angle);
	if (angle > 90) angle = 0;
}

void Test_Servo(void)
{
	MyTimer_Base_Init_ms(TIM3, 100);
	MyTimer_ActiveIT(TIM3,4,Callback_Servo);
	MyTimer_Base_Start(TIM3);
		
	MyServo_Init();
	MyServo_Rotate(90);
	
	while(1);
}

/**********************************************************
								TEST DE LA TELECOMMANDE EN RECEPTION 
**********************************************************/

void	Test_Telcom_RX(void) 
{
	MyUSART_Init(USART1, B_9600);
	
	while(1) {
		MyUSART_Transmit(USART1, "abcdef\r");
	}
}	


/**********************************************************
								TEST DU MOTEUR 
**********************************************************/

void Test_Moteur(void) 
{
	MyMoteur_Init();
	MyMoteur_Start(50, MyMoteur_HORAIRE);
	
	while(1);
}


/**********************************************************
	      TEST DU MOTEUR + TELECOMMANDE (EN EMISSION) 
**********************************************************/

static void Callback_Moteur (void) 
{
	signed char temp = MyUSART_Receive(USART1); 
	if (temp < 0 )
		MyMoteur_Start(-temp, MyMoteur_ANTI_HORAIRE);
	else 
		MyMoteur_Start(temp, MyMoteur_HORAIRE);	
}

void Test_Moteur_Telecom_TX(void) 
{
	MyUSART_Init(USART1, B_9600);
	MyTimer_Base_Init_ms(TIM2, 100);
	MyTimer_ActiveIT(TIM2, 1, Callback_Moteur);
	MyTimer_Base_Start(TIM2);
	
	MyMoteur_Init();
	
	while(1);
}

/**********************************************************
 TEST DU REAL TIME CLOCK (RTC) + TELECOMMANDE(EN RECPTION)
**********************************************************/
static void Callback_RTC(void)
{
	struct horodatage hor;
	MyRTC_Get_Horodatage(&hor);
	char frame[] = {MyRTC_BIN_TO_DIG1(hor.year), 
										MyRTC_BIN_TO_DIG0(hor.year),  ':',
									MyRTC_BIN_TO_DIG1(hor.month), 
										MyRTC_BIN_TO_DIG0(hor.month), ':',
									MyRTC_BIN_TO_DIG1(hor.date),  
										MyRTC_BIN_TO_DIG0(hor.date),  ':',
									MyRTC_BIN_TO_DIG1(hor.day),  
										MyRTC_BIN_TO_DIG0(hor.day),   '-',
									MyRTC_BIN_TO_DIG1(hor.hours), 
										MyRTC_BIN_TO_DIG0(hor.hours), ':',
									MyRTC_BIN_TO_DIG1(hor.mins),  
										MyRTC_BIN_TO_DIG0(hor.mins),  ':',
									MyRTC_BIN_TO_DIG1(hor.secs), 
										MyRTC_BIN_TO_DIG0(hor.secs),  
	  '\r', '\0'};
	
	MyUSART_Transmit(USART1, frame);
	
}

void Test_RTC_Telecom_RX(void)
{
	MyRTC_Init();
	MyTimer_Base_Init_ms(TIM4, 3000);
	MyTimer_ActiveIT(TIM4, 1, Callback_RTC);
	MyTimer_Base_Start(TIM4);
	
	MyUSART_Init(USART1, B_9600);
	
	while(1);
}

/**********************************************************
 TEST DE L'ACCELEROMETRE(IMU) + TELECOMMANDE(EN RECPTION)
**********************************************************/

#define SIGN(x) (((x) < 0) ? '-' : '+')

static void Callback_IMU(void)
{
	static int16_t x, y, z;
	MyIMU_Read_XYZ(&x, &y, &z);
	
	char frame[] = {'x', ':', SIGN(x), 'g', ',', ' ',
									'y', ':', SIGN(y), 'g', ',', ' ',
									'z', ':', SIGN(z), 'g', ',', ' ',
		'\r' ,'\0'};
	
	MyUSART_Transmit(USART1, frame);
}


void Test_IMU_Telecom_RX(void)
{
	MyRTC_Init();
	MyTimer_Base_Init_ms(TIM4, 3000);
	MyTimer_ActiveIT(TIM4, 1, Callback_IMU);
	MyTimer_Base_Start(TIM4);
	
	MyUSART_Init(USART1, B_9600);
	
	while(1);
}

void Test_Roulis_Limite(void)
{
	MyUSART_Init(USART1, B_9600);
	MyIMU_Init();
	
	char frame[MyRTC_HEURE_SIZE + 1];
	
	while(1) {
		float tan_roulis = MyIMU_Get_Roulis_Tang();
		if (tan_roulis < -MY_VOILIER_MAX_ROULIS_TAN || 
							tan_roulis > MY_VOILIER_MAX_ROULIS_TAN) {
				MyRTC_Get_Heure(frame);
			  MyUSART_Transmit(USART1, frame);
				MyUSART_Transmit(USART1, WARNING_MSG_ROULIS);
		} else {
				MyUSART_Transmit(USART1, "Roulis normal\r");
		}
	}
}

/**********************END_OF_FILE****************************/
