#include <stm32f10x.h>
#include "gpiob.h"
#include "SPI_R_W.h"

uint16_t ID_DEV; 
uint8_t SR_1, SR_2, SR_3; 

uint32_t address; 
uint8_t result; 
int operation = 0; 

int main(void)
{
  uint8_t data[256];
	//const uint8_t size = 256;
	
	for(int i = 0; i < 256; i++)
	{
		data[i] = i;
	}
	
	SPI_Init();
	
	// First perform code validation:
	// Read manufacturer ID and device ID
	
	ID_DEV = Flash_ReadID();
	// Read 3 status registers
	SR_1 = Flash_ReadSR(1);
	SR_2 = Flash_ReadSR(2);
	SR_3 = Flash_ReadSR(3);

	
	while(1) {
		if(operation == 0) continue; 
		
		switch(operation) {
			case 1: {
				result = Flash_ReadByte(address); 
				break; 
			}
			case 2: {
				Flash_EraseBlock(0x00000000);
				Flash_WritePage(0x00000000, data);
				break; 
			}
		}
		operation = 0; 
	}
}