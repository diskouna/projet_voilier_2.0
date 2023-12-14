#include "MyGPIO.h"

void MyGPIO_Init(GPIO_TypeDef *GPIO, char GPIO_Pin, char GPIO_Conf)
{
    // Enable clock 
    switch ((uintptr_t)GPIO) {
        case (uintptr_t)GPIOA : 
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
            break;
        case (uintptr_t)GPIOB : 
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
            break;
        case (uintptr_t)GPIOC : 
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
            break;
        case (uintptr_t)GPIOD : 
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
            break;
    }

    // set GPIO's configuration
    if (GPIO_Pin < 8 ) {
        // Use Port Configuration Register Low (CRL)
				GPIO->CRL &= ~(0xF << (4 * GPIO_Pin)); 
        GPIO->CRL |=  (GPIO_Conf << (4 * GPIO_Pin)); 
    } else if (GPIO_Pin < 16) {
        // Use Port Configuration Register HIGB (CRH)
				GPIO->CRH &= ~(0xF << (4 * (GPIO_Pin - 8)));
        GPIO->CRH |=  (GPIO_Conf << (4 * (GPIO_Pin - 8)));
    }
		
		if (GPIO_Conf == In_PullUp)
				GPIO->ODR |= (0x01 << GPIO_Pin);
		else if (GPIO_Conf == In_PullDown)
				GPIO->ODR &= ~(0x01 << GPIO_Pin);
}

int  MyGPIO_Read  (GPIO_TypeDef *GPIO, char GPIO_Pin)
{
    if (GPIO_Pin < 16)
			return (GPIO->IDR >> GPIO_Pin) & 0x1 ;
		return 0;
}

void MyGPIO_Set   (GPIO_TypeDef *GPIO, char GPIO_Pin)
{
    if (GPIO_Pin < 16)
			GPIO->BSRR =  (0x01 << GPIO_Pin);
}

void MyGPIO_Reset (GPIO_TypeDef *GPIO, char GPIO_Pin)
{
    if (GPIO_Pin < 16)
			GPIO->BRR  =  (0x01 << GPIO_Pin);
}

void MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin)
{
    if (GPIO_Pin < 16)
			GPIO->ODR ^=  (0x01 << GPIO_Pin);
}
