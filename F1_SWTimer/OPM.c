#include <stm32f10x.h>
#include "OPM.h"
#include "Button.h"
#include "Timer.h"

void Timer_Init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->PSC = 72 - 1; //setting prescaler
	TIM2->ARR = 50000; //setting auto-reload value
	
	TIM2->SR &= ~TIM_SR_UIF; //Set EGR, clear UIF
	
	TIM2->CR1 |= TIM_CR1_OPM;
	
	TIM2->DIER |= TIM_DIER_UIE; //update interrupt event
	
	NVIC_EnableIRQ(TIM2_IRQn); //IRQ enabling at processor's side(NVIC)
	
	
	
	//TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_IRQHandler(void)
{
	if(TIM2->SR & TIM_SR_UIF)
	{
		TIM2->SR &= ~TIM_SR_UIF;
		
		int idle = 0;
		int run = 1;
		int stop = 2;
		
		if(!(GPIOC->IDR & 0x0100))
		{			
		if(state == idle){
		
			running = 1;
			state = run;
		}
	
		else if (state == run){
		
			running = 0;
			state = stop;
		}
	  else if(state == stop){
		
			ms = 0;
			sec = 0;
			min = 0;
			state = idle;
		}
	}
 }
}