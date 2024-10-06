#include <stdint.h>
#include <GPIO_Driver.h>
#include <Display_Driver.h>
#include <Delay.h>

#define Delay() Sys_DelayUs(1)

void DisplayDrv_Init(void)
{
	GPIO_Init();
}

void Display_driver_Sel_Digit(int digit)
{
	GPIO_SelDigit(digit);
}

void Display_Driver_ShowPattern(uint8_t pattern)
{for(int i = 0; i < 8; i++) {
		if(pattern & 0x1) {
			GPIO_SetSrDat(); 
		}
		else {
			GPIO_ClrSrDat(); 
		}
		pattern = pattern >> 1; 
		Delay(); 
		GPIO_SetSrClk(); 
		Delay(); 
		GPIO_ClrSrClk(); 
		Delay(); 
	}
	
	GPIO_SetSrLe(); 
	Delay(); 
	GPIO_ClrSrLe(); 
	Delay(); 
	
}

	

