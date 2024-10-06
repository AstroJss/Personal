#ifndef Display_Driver_H_
#define Display_Driver_H_

#include <stdint.h>

extern void DisplayDrv_Init(void);

extern void Display_driver_Sel_Digit(int digit);

extern void Display_Driver_ShowPattern(uint8_t pattern);

#endif


