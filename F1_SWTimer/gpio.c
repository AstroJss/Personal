#include <stm32f10x.h>
#include "gpio.h"

//System Clock Configuration
//void SystemInit();

//GPIO Initialization
void GPIO_Init(void)
{
	RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN); //enabling ports B and C
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; //enabling alternate function port
	AFIO->MAPR = (AFIO->MAPR & 0xF8FFFFFF) | 0x02000000; //disabling AF
	// Set PB4 to default value (0)
	GPIOB->BRR = 0x0010; 
	GPIOC->BSRR = 0x0100;
	GPIOB->CRL = (GPIOB->CRL & 0xFF000FFF) | 0x00333000; //PB3-5
	GPIOC->CRH = (GPIOC->CRH & 0xFFF000F0) | 0x00033308; //PC8af and PC10-12
}

void GPIO_Button(void)
{
	GPIOC->IDR |= (GPIOC->IDR & 0xFFFFFEFF) | 0x100; //enabling pull-up resistor
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
	GPIOB->BSRR = 0x0010; 
}

void GPIO_ClrSrLe(void) {
	// PB4
	GPIOB->BRR = 0x0010; 
}

void GPIO_SetSrClk(void) {
	// PB5
	GPIOB->BSRR = 0x0020; 
}

void GPIO_ClrSrClk(void) {
	// PB5
	GPIOB->BRR = 0x020; 
}

void GPIO_SelDigit(int value) {
	// PC10~12
	GPIOC->ODR = (GPIOC->ODR & 0xE3FF) | (value & 0x7) << 10; 
}


