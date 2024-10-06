#include <stm32f10x.h>
#include "gpiob.h"

uint8_t Flash_ReadByte(uint32_t addr) {
	// chip select
	CS_Low(); 
	// instruction phase
	SPI_Exchange(0x03); 
	// address phase
	SPI_Exchange((addr >> 16) & 0xFF); 
	SPI_Exchange((addr >> 8) & 0xFF); 
	SPI_Exchange(addr & 0xFF); 
	// data phase
	uint8_t byte = SPI_Exchange(0x00); 
	//chip deselect
	CS_High(); 
	return byte;
}

void Flash_EraseBlock(uint32_t addr)
{
	//write enable
	Flash_WriteEnable();
	//chip select
	CS_Low();
	//instruction phase
	SPI_Exchange(0xD8);
	//address phase
	SPI_Exchange((addr >> 16) & 0xFF);
	SPI_Exchange((addr >> 8) & 0xFF);
	SPI_Exchange(addr & 0xFF);
	//chip deselect
	CS_High();
	//wait until the erase cycle is complete
	while(Flash_CheckBusy())
	{
		
	};
}

// Page 17: 0x01100 ~ 0x011FF (inclusive)

void Flash_WritePage(uint32_t addr, const uint8_t *data) {
	// 
	Flash_WriteEnable();
	// chip select
	CS_Low(); 
	// instruction phase
	SPI_Exchange(0x02); 
	// address phase
	SPI_Exchange((addr >> 16) & 0xFF); 
	SPI_Exchange((addr >> 8) & 0xFF); 
	SPI_Exchange(addr & 0xFF); 
	// data phase
	for(int i = 0; i < FLASH_PAGE_SIZE; i++) {
		SPI_Exchange(data[i]); 
	}
	
	// chip deselect
	CS_High(); 
}

uint8_t Flash_ReadSR(int SR_num)
{
	uint8_t instruction; 
	
	// your switch case
	switch(SR_num)
	{
		case 1: 
			instruction = 0x05; 
		break; 
		
		case 2:
			instruction = 0x35; 
		break;
		
		case 3: 
			instruction = 0x15;	
		break;
		
		default: 
			
		return 0x0000; 
	}
	CS_Low();
	
	SPI_Exchange(instruction); 
	
	uint8_t read = SPI_Exchange(0x00);
	
	CS_High();
	
	return(read);
}

uint16_t Flash_ReadID(void)
{
	CS_Low();
	
	SPI_Exchange(0x90);
	
	SPI_Exchange(0x00);
	SPI_Exchange(0x00);
	SPI_Exchange(0x00);
	
	uint8_t manuf_id = SPI_Exchange(0x00);
	uint8_t device_id = SPI_Exchange(0x00);
	
	return((manuf_id << 8) | device_id);
}