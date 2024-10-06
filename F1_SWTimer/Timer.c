#include <stm32f10x.h>
#include "Timer.h"
#include "DisplayDrv.h"
#include "gpio.h"

volatile uint8_t running = 0; //stopwatch running flag
//volatile uint8_t seconds = 0;

//#define  RCC_APB1ENR_TIM3EN   ((uint32_t)0x00000010)
 
//function to initialize timer 6
void Timer_Config(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //enabling timer 6
	
	TIM3->PSC = 72 - 1; //setting prescaler value
	TIM3->ARR = 1250 - 1; //setting auto-reload value
	
	// Set EGR, clear UIF
	TIM3->SR &= ~TIM_SR_UIF;
	
	TIM3->DIER |= TIM_DIER_UIE; //update interrupt event
	
	NVIC_EnableIRQ(TIM3_IRQn); // IRQ enabling at processor side (NVIC)
	
	TIM3->CR1 |= TIM_CR1_CEN; //enabling counter
}

// 1.25ms timebase - divided by 8 - 10ms timebase
// 10ms timebase conditionally increments the ms/s/min counter (3 GV) [EX1]
// every 1.25 ms refersh screen based on patterns <= ms/s/min GVs [EX2]

int min = 0;
int sec = 0;
int ms = 0;

volatile uint8_t patterns[8]; // Stores content currently being displayed (like display RAM)

void Call_every_10(void) {
	
	// Increase min sec ms
	
	if(running)
	{
	ms++;
	if(ms == 100)
	{
		sec++;
		ms = 0;
		if(sec == 60)
		{
			min++;
			sec = 0;
			if(min == 60)
			{
				min = 0;
			}
		}
	}
	
}
	
	// Generate new patterns[]
	// I have min, sec, ms
	// I need to get patterns[0~7]
	
	// Fill out the structure
	patterns[2] = 0x02; 
	patterns[5] = 0x02; 
	
	// Fill out the 2 ms digits
	uint8_t segment_map[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
	patterns[7] = segment_map[ms % 10]; 
	patterns[6] = segment_map[ms / 10]; 
	patterns[4] = segment_map[sec % 10];
	patterns[3] = segment_map[sec / 10];
	patterns[1] = segment_map[min % 10];
	patterns[0] = segment_map[min / 10];
}


void Call_every_1_25(void)
{
	static int index = 0;
	
	if(index == 0) {
		// Right before one new round
		// Advance counter
		Call_every_10(); 
	}
	
	// One step of refreshing
	uint8_t pattern = patterns[index];
	Shift_Register_Write(0);
	GPIO_SelDigit(index);
	Shift_Register_Write(pattern);
	index++;
	if(index >= 8)
		index = 0;
}

void TIM3_IRQHandler(void)
{
	if(TIM3->SR & TIM_SR_UIF)
	{
		TIM3->SR &= ~TIM_SR_UIF;
	
		Call_every_1_25();
	
	}
}




