#include <stm32f10x.h>
#include "Timer.h"
#include "gpio.h"
#include "Button.h"

int state = 0;

//configuring the external interrupt
void EXTI_Config(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; //enable AFIO
	
	AFIO->EXTICR[2] &= ~AFIO_EXTICR3_EXTI8; //clearing bits in EXTI8 
	AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI8_PC; //enabling EXTI on PB8
	
	EXTI->FTSR |= EXTI_FTSR_TR8; //set falling edge trigger for the button
	EXTI->RTSR |= EXTI_RTSR_TR8; //disble the rising edge trigger for the button
	
	// Clear EXTI interrupt flag
	EXTI->PR |= (1 << 8);
	
	// Peripheral side enable
	EXTI->IMR |= EXTI_IMR_MR8; //enable (unmask) EXTI8 interrupt
	EXTI->EMR |= ~EXTI_EMR_MR8; //disble (mask) EXTI8 event
	
	// Kernel side enable
	NVIC->ISER[0] |= (1 << EXTI9_5_IRQn); 
}

//external interrupt for the button
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & EXTI_PR_PR8)
	{
		EXTI->PR |= EXTI_PR_PR8;
		
		TIM2->CNT = 0;
		
		TIM2->CR1 |= TIM_CR1_CEN;
		
		//running = !running;
			
		
	
	}
}
