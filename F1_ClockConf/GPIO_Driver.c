#include <stm32f10x.h>

#include <GPIO_Driver.h>

void GPIO_Init(void) {
	// PB3-5, PC10-12:
	// GP PP Ouput Max speed 50 MHz
	RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN); 
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 
	AFIO->MAPR = (AFIO->MAPR & 0xF8FFFFFF) | 0x02000000; 
	GPIOB->CRL = (GPIOB->CRL & 0xFF000FFF) | 0x00333000; 
	GPIOC->CRH = (GPIOC->CRH & 0xFFF000FF) | 0x00033300; 
}

void GPIO_SetSrDat(void) {
	// PB3
	GPIOB->BSRR = 0x0008; 
}

void GPIO_ClrSrDat(void) {
	// PB3
	GPIOB->BRR = 0x0008; 
}

void GPIO_SetSrLe(void) {
	// PB4
	GPIOB->BSRR = 0x010; 
}

void GPIO_ClrSrLe(void) {
	// PB4
	GPIOB->BRR = 0x010; 
}

void GPIO_SetSrClk(void) {
	// PB5
	GPIOB->BSRR = 0x020; 
}

void GPIO_ClrSrClk(void) {
	// PB5
	GPIOB->BRR = 0x0020; 
}

void GPIO_SelDigit(int value) {
	// PC10-12
	GPIOC->ODR = (GPIOC->ODR & 0xE3FF) | ((value & 0x7) << 10); 
}


