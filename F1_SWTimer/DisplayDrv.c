#include <stm32f10x.h>
#include "gpio.h"
#include "Timer.h"

/*void  DispDrv_Init(void)
{
	GPIO_Init();
}

void DispDrv_SelectDigit(int digit)
{
	GPIO_SelDigit(digit);
}*/


#define delay() Sys_DelayUs(1)

void Sys_DelayUs(uint32_t time) {
	SysTick->CTRL = 0x0; 
	SysTick->VAL = 0x0; 
	SysTick->LOAD = time * 9 - 1; // 72MHz
	SysTick->CTRL = 0x1; 
	while(!(SysTick->CTRL & 0x10000)); 
	SysTick->CTRL = 0x0; 
}

void Sys_DelayMs(uint32_t time) {
	for(uint32_t i = 0; i < time; i++) 
		Sys_DelayUs(1000); 
}

void Shift_Register_Write(uint8_t pattern)
{
	for(int i = 0; i < 8; i++)
	{
		if(pattern & 0x1){
			GPIO_SetSrDat();
		}
		else {
			GPIO_ClrSrDat();
		}
		
		pattern = pattern >> 1;
		delay();
		GPIO_SetSrClk();
		delay();
		GPIO_ClrSrClk();
		delay();
	}
	
	GPIO_SetSrLe();
	delay();
	GPIO_ClrSrLe();
	delay();
}

