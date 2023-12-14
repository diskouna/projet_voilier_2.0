#ifndef MYIMU_H
#define MYIMU_H

/*
-- * 	**IO SPI 1**
	SPI1_NSS PA4
	SPI1_SCK PA5
	SPI1_MISO  PA6  
	SPI1_MOSI  PA7
--ADXL 345
*/

#include "stm32f10x.h"
#include "MySPI.h"


#define ADXL345_POWER_CTL_ADDR           '\x2D'
#define ADXL345_POWER_CTL_MEASURE_MODE   '\x08'

#define ADXL345_BW_RATE_ADDR             '\x2C'
#define ADXL345_BW_RATE_100Hz            '\x0A'

#define ADXL345_DATA_FORMAT_ADDR        '\x31'
#define ADXL345_DATA_FORMAT_FULL_RES    '\x08'
#define ADXL345_DATA_FORMAT_RIGHT_JUST  '\x00'
#define ADXL345_DATA_FORMAT_LEFT_JUST   '\x04'
#define ADXL345_DATA_FORMAT_RANGE_16G   '\x03'

#define ADXL345_DATA_BASE     '\x32'
// DATAX = (DATAX1 << 8) | DATAX0
#define ADXL345_DATAX0_ADDR   (ADXL345_DATA_BASE + '\x00')
#define ADXL345_DATAX1_ADDR   (ADXL345_DATA_BASE + '\x01')

// DATAY = (DATAY1 << 8) | DATAY0
#define ADXL345_DATAY0_ADDR   (ADXL345_DATA_BASE + '\x02')
#define ADXL345_DATAY1_ADDR   '\x35'

// DATAZ = (DATAZ1 << 8) | DATAZ0
#define ADXL345_DATAZ0_ADDR   '\x36'
#define ADXL345_DATAZ1_ADDR   '\x37'

#define ADXL345_READ 				'\x80'
#define ADXL345_WRITE       '\x00'

#define ADXL345_SINGLEBYTE  '\x00'
#define ADXL345_MULTIBYTE   '\x40'

void MyIMU_Init(void);

void MyIMU_Read_XYZ(int16_t *x, int16_t *y, int16_t *z );

float MyIMU_Get_Roulis_Tang(void);

#endif //MYIMU_H
