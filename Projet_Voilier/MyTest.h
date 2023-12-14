/**************************************************************
 * @file  MyTest.h
 * @brief Ce fichier header contient la déclaration des tests 
 *        unitaire et d'intégration des differents composants 
 *        du voilier
 *
 *************************************************************/
 
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

/**
 * @fn    void Test_Servo(void)
 * @brief TEST DU SERVOMOTEUR
 */
void Test_Servo(void);

/**
 * @fn    void Test_Telecom_RX(void)
 * @brief TEST DE LA TELECOMMANDE EN RECEPTION
 */
void Test_Telecom_RX(void); 

/**
 * @fn    void Test_Moteur(void)
 * @brief TEST DU MOTEUR
 */
void Test_Moteur(void) ;

/**
 * @fn    void Test_Moteur_Telecom_TX(void)
 * @brief TEST DU MOTEUR + TELECOMMANDE (EN EMISSION)
 */
void Test_Moteur_Telecom_TX(void);

/**
 * @fn     void Test_RTC_Telecom_RX(void)
 * @brief  TEST DU REAL TIME CLOCK (RTC) + 
 *															TELECOMMANDE(EN RECPTION
 */
void Test_RTC_Telecom_RX(void);

/**
 * @fn     void Test_IMU_Telecom_RX(void)
 * @brief  TEST DE L'ACCELEROMETRE(IMU) + 
 *															TELECOMMANDE(EN RECPTION)
 */
void Test_IMU_Telecom_RX(void);

#endif //MYTEST_H

/**********************END_OF_FILE****************************/