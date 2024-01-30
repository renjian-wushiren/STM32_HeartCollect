#ifndef __DRI_ADC_H__
#define __DRI_ADC_H__
#include "Util.h"
    void Dri_ADC1_Init(void);
    void Dri_ADC1_Start(void);
    void Dri_ADC1_Stop(void);
    uint16_t Dri_ADC1_GetValue(void);
#endif