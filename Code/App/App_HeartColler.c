#include "App_HeartColler.h"
#include "Debug.h"
static uint16_t heart_duration;  // 采样时长
static uint16_t heart_collectMS; // 多少ms进行1次采样
static uint16_t tim7_count;      // 中断次数
uint8_t isToReadAdcV = 0;
/**
 * @brief 开始函数
 * 
 * @param rate 采样率
 * @param duraion 采样时长
 */
void APP_HeartCollect_Start(uint16_t rate, uint16_t duraion)
{
    heart_duration  = duraion * 1000;
    heart_collectMS = 1000 / rate;
    Dri_ADC1_Init();
    Dri_ADC1_Start();
    Dri_TIM7_Init();
    Dri_TIM7_Start();
}
/**
 * @brief 结束函数
 * 
 */
void APP_HeartCollect_Stop(void)
{
    Dri_ADC1_Stop();
}
/**
 * @brief
 *
 */
void TIM7_UpInterruptCallBuck(void)
{
    tim7_count++;
    if (tim7_count >= heart_duration) {
        Dri_TIM7_Stop();
        return;
    }
    if (tim7_count % heart_collectMS == 0) {
        isToReadAdcV = 1;
    }
}
/**
 * @brief 读取心电数据
 *
 * @return uint16_t
 */
uint16_t APP_HeartCollect_ReadHeartData(void)
{
    while (isToReadAdcV == 0)
        ;
    isToReadAdcV = 0;
    return Dri_ADC1_GetValue();
}
