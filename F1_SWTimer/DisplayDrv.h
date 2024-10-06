#ifndef DISPLAYDRV_H_
#define DISPLAYDRV_H_

#include <stm32f10x.h>

extern uint8_t segment_map[];

extern void Shift_Register_Write(uint8_t data);
extern void Display_Digits(uint8_t num);

#endif 