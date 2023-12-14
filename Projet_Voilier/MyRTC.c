#include "MyRTC.h"

//L'Horloge temps réel utilisé est le DS1307
// 
// hours is used in 24-hour mode 
 

void  MyRTC_Init(void) 
{
	MyI2C_Init(I2C1, 15, NULL); 
//#ifdef(MYVOILIER_CONFIGURE_RTC_TIME)
//	struct horodatage hor = (struct horodatage) {
//			.secs = '\x00',
//			.mins = '\x21',
//		  .hours= '\x10',  /* 24-hour mode : 09h */
//		  .day  = '\x03',  /* 0 : SUN, 1 : MON, ...*/
//			.date = '\x29',
//			.month= '\x11',
//			.year = '\x23'
//	};
//	
//	MyI2C_PutString(I2C1, 0x00, &(MyI2C_RecSendData_Typedef) {.SlaveAdress7bits = MYRTC_ADDRESS,
//																													 .Ptr_Data  = &hor.secs,
//																													 .Nb_Data = 7					
//																													});
//#endif
}

void MyRTC_Get_Horodatage(struct horodatage *hor)
{
	MyI2C_GetString(I2C1, 0x00, &(MyI2C_RecSendData_Typedef) {.SlaveAdress7bits = MYRTC_ADDRESS,
																													 .Ptr_Data  = &(hor->secs),
																													 .Nb_Data = 7					
																});
}

void MyRTC_Get_Heure(char horo[])
{
	struct horodatage hor;
	MyRTC_Get_Horodatage(&hor);
	
	horo[0] = MyRTC_BIN_TO_DIG1(hor.hours);
	horo[1] = MyRTC_BIN_TO_DIG0(hor.hours); 
	horo[2] = 'h';
	horo[3] = MyRTC_BIN_TO_DIG1(hor.mins);
  horo[4] = MyRTC_BIN_TO_DIG0(hor.mins); 
	horo[5] = 'm';
	horo[6] = MyRTC_BIN_TO_DIG1(hor.secs);
  horo[7] = MyRTC_BIN_TO_DIG0(hor.secs);
	horo[8] = 's';
}

