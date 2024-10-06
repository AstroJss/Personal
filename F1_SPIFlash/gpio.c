#include <stm32f10x.h>

#define FLASH_PAGE_SIZE   256

#define CS_Low()   GPIOB->BRR = GPIO_BRR_BR12 //set Chip Select low
#define CS_High()  GPIOB->BSRR = GPIO_BSRR_BS12 //set CHip Select High

void SPI_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //enalbe SPI and GPIOB clocks
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN; 
	
	GPIOB->CRH = ((GPIOB->CRH & 0x0000FFFF) | 0xB4B30000); //configuring the 4 SPI pins
	
	CS_High(); //SET CS high (deselect)
	
	SPI2->CR1 = SPI_CR1_CPHA | SPI_CR1_CPOL | SPI_CR1_MSTR | SPI_CR1_BR | SPI_CR1_SSM | 
	            SPI_CR1_SSI; //configuring SPI2
	
	
	SPI2->CR1 |= SPI_CR1_SPE; //enabling SPI at the last since some features won't get confgured if SPI is enabled
	
}

uint8_t SPI_Exchange(uint8_t data)
{
	//wait till the tx buffer is empty
	while(!(SPI2->SR & SPI_SR_TXE))
	{
		//waiting for the tx buffer to be empty
	}
	
	SPI2->DR = data;
	
	//wait till the rx buffer is full
	while(!(SPI2->SR & SPI_SR_RXNE))
	{
		//waiting for the rx buffer to be full
	}
	
	return SPI2->DR;
}

void Flash_WriteEnable(void)
{
	CS_Low();
	SPI_Exchange(0x06);
	CS_High();
}

uint8_t Flash_CheckBusy(void)
{
	uint8_t status;
	//chip select
	CS_Low();
	//instruction phase
	SPI_Exchange(0x05);
	//read SR
	status = SPI_Exchange(0x00);
	//deselect chip
	CS_High();
	
	return(status & 0x00000001);
}
