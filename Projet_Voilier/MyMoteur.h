#ifndef MYMOTEUR_H
#define MYMOTEUR_H

#include "MyGPIO.h"
#include "MyTimer.h"

/* 
 -- TIM3.4 = PB.1: pwm 
 -- sens   = PB2
*/

typedef enum {
	MyMoteur_HORAIRE,
	MyMoteur_ANTI_HORAIRE,
} MyMoteur_sens_t;


void MyMoteur_Init(void);

/* 
  vit_per.min =   0% 
  vit_per.max = 100%
*/
void MyMoteur_Start(char vit_per, MyMoteur_sens_t sens);

void MyMoteur_Stop(void);

#endif //MYMOTEUR_H
