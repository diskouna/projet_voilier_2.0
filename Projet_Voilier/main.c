#include "MyVoilier.h"

#include "MyServo.h"
#include "MyTimer.h"
#include "MyMoteur.h"
#include "MyUSART.h"
#include "MyRTC.h"
#include "MyIMU.h"
#include "MyComm.h"
#include "TENSION_BATTERIES.h"
#include "BORDAGE_AUTOMMATIQUE.h"
#include "GIROUETTE.h"


/*
TODO : 
	--- add length to "string" function 
  --- arbitrer l'utilisation de l'USART : warning et envoie normal 
  --- add test 
*/

void MyVoilier_set_vitesse(signed char new_vitesse)
{
	static signed char old_vitesse = 0;
	if (old_vitesse != new_vitesse) {
		old_vitesse = new_vitesse;
		if (new_vitesse < 0 )
			MyMoteur_Start(-new_vitesse, MyMoteur_ANTI_HORAIRE);
		else 
			MyMoteur_Start(new_vitesse, MyMoteur_HORAIRE);	
	}
}

void MyVoilier_get_frame(char frame[])
{
	// heure format : hh:mm:ss
	MyRTC_Get_Heure(frame); 	//use return value : boolean 

	*(frame  + MyRTC_HEURE_SIZE + 1) = '\r';
  //MyVoilier_Get_Status(frame + MyRTC_HEURE_SIZE);
	//memcpy ? 
}

void MyVoilier_Test_Roulis(void)
{
	  char frame[MyRTC_HEURE_SIZE + 1];
		float tan_roulis = MyIMU_Get_Roulis_Tang();
		
	  if (tan_roulis < -MY_VOILIER_MAX_ROULIS_TAN || tan_roulis > MY_VOILIER_MAX_ROULIS_TAN) {
				MyRTC_Get_Heure(frame);
			  MyComm_Transmit(frame);
				MyComm_Transmit(WARNING_MSG_ROULIS);
		}
}

int main()
{
	/**********************************************************
		      INITIALISATION DES PERIPHERIQUES DU VOILIER
	**********************************************************/
 	MyMoteur_Init();
  MyRTC_Init();
	MyIMU_Init();
	MyServo_Init();
	initialisation_compteur_girouette ();
	initialisation_interuption_girouette ();
	init_tension_batterie();
	
	MyComm_Init(MyVoilier_get_frame, MyVoilier_set_vitesse);

	//MyComm_Transmit(MyVoilier_Image); //Batteau Init : Message
	
	while(1) {
		test_tension_batterie();
		bordage(get_angle_girouette());
		MyVoilier_Test_Roulis();
	}
	
	return 0;
}

/**********************************************************
		                 STATUS  MESSAGE
**********************************************************/

char STATUS_MSG[] = "VOILIER INITIALISE\r";
	
/**********************************************************
		                WARNING  MESSAGE
**********************************************************/
char WARNING_MSG_ROULIS[]   = "Roulis Trop Eleve\r"; 
char WARNING_MSG_BATTERIE[] = "Batterie Trop Faible\r";


char MyVoilier_Image[] = 
													"                     /|___        " EOL
													"                   ///|   ))      " EOL
													"                 /////|   )))     " EOL
													"               ///////|    )))    " EOL
													"             /////////|     )))   " EOL
													"           ///////////|     ))))  " EOL
													"         /////////////|     )))   " EOL
													"        //////////////|    )))    " EOL
													"      ////////////////|___)))     " EOL
													"        ______________|________   " EOL
													"        \\                     /  " EOL
													"      ~~~~~~~~~~~~~~~~~~~~~~~~~~~ " EOL;

/********************************************************************

*********************************************************************/