#ifndef GPIO_Driver_H_
#define GPIO_Driver_H_

extern void GPIO_Init(void);
extern void GPIO_SetSrDat(void);
extern void GPIO_ClrSrDat(void);
extern void GPIO_SetSrLe(void);
extern void GPIO_ClrSrLe(void);
extern void GPIO_SetSrClk(void);
extern void GPIO_ClrSrClk(void);
extern void GPIO_SelDigit(int value);

#endif







