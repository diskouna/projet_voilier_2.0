#ifndef MYVOILIER_H
#define MYVOILIER_H

/*
	--Add watchdog configuration 

*/

#define MY_VOILIER_MAX_ROULIS_TAN 0.839f //40°

#define EOL  "\r"  //End of Line

/* STATUS MESSAGE */
extern char STATUS_MSG[];

		
/* WARNING MESSAGE */
extern char WARNING_MSG_ROULIS[];  
extern char WARNING_MSG_BATTERIE[];

extern char MyVoilier_Image[];



/*

CARTE NUCLEO : 
	Attention : ne pas utilisez les broches 
	PA2, PA3, PA5, PA13, PA14, PA15, PB3, PB4, 
	PC13, PC14 et PC15 qui
	sur cette carte nucléo sont déjà utilisées (PA5 pour le led verte par exemple).

*/


/*         CALLBACK        */

#endif //MYVOILIER_H
