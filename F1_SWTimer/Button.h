#ifndef BUTTON_H_
#define BUTTON_H_
#include <stm32f10x.h>

extern int state;
extern void EXTI_Config(void);
extern void EXTI9_5_IRQHandler(void);

#endif