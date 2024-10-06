#ifndef GPIO_H_ 
#define GPIO_H_
#include <stm32f10x.h>

#define FLASH_PAGE_SIZE 256;
#define CS_Low()   GPIOB->BRR = GPIO_BRR_BR12; //set Chip Select low
#define CS_High()  GPIOB->BSRR = GPIO_BSRR_BS12; //set CHip Select High

extern void SPI_Init(void);
extern uint8_t SPI_Exchange(uint8_t data);
extern void Flash_WriteEnable(void);


#endif