#ifndef __APP_COMMUCATION_H__
#define __APP_COMMUCATION_H__
#include "Dri_USART1.h"
#include <stdlib.h>

void App_Commucation_Init(void);
void App_Commucation_Start(void);
void App_Commucation_Stop(void);
void App_Commucation_CommandProcess(uint16_t *rate, uint16_t *duration);
void App_Commucation_SendData(uint16_t data);
#endif