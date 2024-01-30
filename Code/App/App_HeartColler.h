#ifndef __APP_HEARTCOLLER_H__
#define __APP_HEARTCOLLER_H__
#include "Util.h"
<<<<<<< HEAD
#include "Dri_ADC.h"
#include "Dri_Tim6.h"
#endif
=======
#include "Dri_ADC1.h"
#include "Dri_Tim7.h"

void APP_HeartCollect_Start(uint16_t rate, uint16_t duraion);
void APP_HeartCollect_Stop(void);
uint16_t APP_HeartCollect_ReadHeartData(void);
#endif

>>>>>>> 994a28c (水质检测项目)
