<<<<<<< HEAD
#include "Application.h"
#include "Debug.h"
=======
#include "App_HeartColler.h"
#include "Debug.h"
static uint16_t heart_duration;  // ²ÉÑùÊ±³¤ms
static uint16_t heart_collectMS; // ¶àÉÙmsÖ´ÐÐÒ»´Î²ÉÑù
static uint16_t tim7_count;      // ¶¨Ê±Æ÷ÖÐ¶Ï´ÎÊý
uint8_t isToReadAdcV = 0;
/**
 * @brief ¿ªÊ¼²É¼¯ÐÄµçÍ¼
 *
 * @param rate ²ÉÑùÂÊ
 * @param duraion ²ÉÑùÊ±³¤
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
 * @brief Í£Ö¹²É¼¯ÐÄµçÍ¼
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
 * @brief ¶ÁÈ¡ÐÄµçÊý¾Ý¼´ADCµÄÖµ
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
>>>>>>> 994a28c (æ°´è´¨æ£€æµ‹é¡¹ç›®)
