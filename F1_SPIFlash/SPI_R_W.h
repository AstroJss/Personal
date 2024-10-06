#ifndef SPI_R_W_H_
#define SPI_R_W_H_
#include <stm32f10x.h>

extern uint8_t Flash_ReadByte(uint32_t addr);
extern void Flash_EraseBlock(uint32_t addr);
extern void Flash_WritePage(uint32_t addr, const uint8_t *data);

extern uint8_t Flash_ReadSR(int SR_num);
extern uint16_t Flash_ReadID(void);

#endif