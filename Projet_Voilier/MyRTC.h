#ifndef MYRTC_H
#define MYRTC_H

/* I2C1 : 
		SCL PB6
		SDA PB7
*/

// The DS1307 operates in the standard mode (100kHz) only.
// 7-bit DS1307 address, which is 1101000
#include "stm32f10x.h"
#include "MyI2C.h"
#include <stddef.h>

#define MYRTC_ADDRESS  '\x68' //0b1101000

struct horodatage {
	char secs;
	char mins;
	char hours;
	char day;
	char date;
	char month;
	char year;
};

#define MyRTC_HEURE_SIZE 8

void MyRTC_Init(void);
void MyRTC_Get_Horodatage(struct horodatage *hor);
void MyRTC_Get_Heure(char horo[]);

#define MyRTC_BIN_TO_DIG0(bcd_8) (((bcd_8) & 0xF) + '0')
#define MyRTC_BIN_TO_DIG1(bcd_8) (((bcd_8 >> 4) & 0x7) + '0')

#endif //MYRTC_H
