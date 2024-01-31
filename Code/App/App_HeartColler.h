#ifndef __APP_HEARTCOLLER_H__
#define __APP_HEARTCOLLER_H__
#include "Util.h"
#include "Dri_ADC1.h"
#include "Dri_Tim7.h"

void APP_HeartCollect_Start(uint16_t rate, uint16_t duraion);
void APP_HeartCollect_Stop(void);
uint16_t APP_HeartCollect_ReadHeartData(void);
#endif

