#include "MyIMU.h"
#include "math.h"

void MyIMU_Init(void)
{
	MySPI_Init(SPI1);
	
	MySPI_Clear_NSS();
	MySPI_Send(ADXL345_WRITE | ADXL345_SINGLEBYTE | ADXL345_POWER_CTL_ADDR);
	MySPI_Send(ADXL345_POWER_CTL_MEASURE_MODE);
	MySPI_Set_NSS();
	
	MySPI_Clear_NSS();
	MySPI_Send(ADXL345_WRITE | ADXL345_SINGLEBYTE | ADXL345_BW_RATE_ADDR);
	MySPI_Send(ADXL345_BW_RATE_100Hz);
	MySPI_Set_NSS();
	
	MySPI_Clear_NSS();
	MySPI_Send(ADXL345_WRITE | ADXL345_SINGLEBYTE | ADXL345_DATA_FORMAT_ADDR);
	MySPI_Send(ADXL345_DATA_FORMAT_FULL_RES | ADXL345_DATA_FORMAT_RANGE_16G | ADXL345_DATA_FORMAT_RIGHT_JUST);
	MySPI_Set_NSS();
	
}

void MyIMU_Read_XYZ(int16_t *x, int16_t *y, int16_t *z )
{
	*x = *y = *z = 0; 
	MySPI_Clear_NSS();
	MySPI_Send(ADXL345_READ | ADXL345_MULTIBYTE | ADXL345_DATA_BASE);
	
	*x |= MySPI_Read();
	*x |= (MySPI_Read() << 8);
	
	*y |= MySPI_Read();
	*y |= (MySPI_Read() << 8);
	
	*z |= MySPI_Read();
	*z |= (MySPI_Read() << 8);
	
	MySPI_Set_NSS();
}

float MyIMU_Get_Roulis_Tang(void)
{
	int16_t x, y, z;
	MyIMU_Read_XYZ (&x, &y, &z);
	
	return ((float)y/(float)z);
}
