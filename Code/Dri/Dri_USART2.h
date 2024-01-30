#ifndef __DRI_USART2_H__
#define __DRI_USART2_H__
#include "Util.h"

void Dri_USART2_Init(void);
void Dri_USART2_Start(void);
void Dri_USART2_Stop(void);
uint8_t Dri_USART2_ReceiveChar(void);
void Dri_USART2_SendChar(uint8_t c);
void Dri_USART2_SendString(uint8_t *str, uint32_t len);
#endif