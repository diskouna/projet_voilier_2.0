#ifndef MYSERVO_H
#define MYSERVO_H

#include "MyTimer.h"


/* Ce module utile : 
    -- la voie 1 du  TIM 1 pour le contrôle du servomoteur 
    --> PA8	 
*/

void MyServo_Init(void);

/*
	angle.min =  0°
  angle.max	= 90°
*/
void MyServo_Rotate(unsigned char angle);

#endif //MYSERVO_H
