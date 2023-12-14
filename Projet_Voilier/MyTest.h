#ifndef MYTEST_H
#define MYTEST_H

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


void Test_Servo(void);
void Test_Telecom_RX(void); 
void Test_Moteur(void) ;
void Test_Moteur_Telecom_TX(void);
void Test_RTC_Telecom_RX(void);
void Test_IMU_Telecom_RX(void);


#endif //MYTEST_H
