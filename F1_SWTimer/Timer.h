#ifndef TIMER_H_
#define TIMER_H_

#include <stm32f10x.h>

extern int min, sec, ms;

extern volatile uint8_t running;
extern volatile uint8_t seconds;

extern void Timer_Config(void);
extern void TIM3_IRQHandler(void);

#endif 