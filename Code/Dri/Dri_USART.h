#ifndef __DRI_USART_H__
#define __DRI_USART_H__

#include "Util.h"
#include <stdio.h>
void Dri_USART_Init();

void Dri_USART1_Sendchar(uint8_t byte);

// void Dri_USART3_Sendchar(uint8_t byte);

// void Dri_USART3_SendStr(uint8_t *str, uint8_t len);

uint8_t Dri_USART1_ReceiveChar();

uint8_t Dri_USART3_ReceiveChar();

void Dri_USART1_ReceiveStr(uint8_t * str, uint8_t * len);

// void Dri_USART3_ReceiveStr(uint8_t *str, uint8_t *len);

void USART1_IRQHandler(void);



#endif

