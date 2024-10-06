#include <stm32f10x.h>
#include <Delay.h>

void Sys_DelayUs(uint32_t time)
{
	SysTick->CTRL = 0x0;
	SysTick->VAL = 0x0;
	SysTick->LOAD = time * 9 - 1;
  SysTick->CTRL = 0x1;
	while(!(SysTick->CTRL & 0x10000)) {
		
	}
	SysTick->CTRL = 0x0;
}

void Sys_DelayMs(uint32_t time)
{
	for(uint32_t i=0; i < time; i++)
	Sys_DelayUs(1000);
}