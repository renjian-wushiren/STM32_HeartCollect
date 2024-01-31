#include "App_Commucation.h"
#include "Debug.h"
#include <string.h>
uint8_t recRete[10] = {0}; // 接收采样率
uint8_t recDura[10] = {0}; // 接收采样时长
uint8_t isRecSussed = 0;   // 是否接收成功
/**
 * @brief 
 *
 * @param buf 缓存数组
 * @param len 长度
 */
void USART1_Callback(uint8_t buff[], uint8_t len)
{
    if (buff[0] == 's') { 
        memcpy(recRete, &buff[1], len - 2);
    } else if (buff[0] == 'c') { // ???????¤????????
        memcpy(recDura, &buff[1], len - 2);
        isRecSussed = 1;
    }
}
/**
 * @brief 初始化
 * 
 */
void App_Commucation_Init(void)
{
    Dri_USART1_Init();
}
/**
 * @brief 开始函数
 * 
 */
void App_Commucation_Start(void)
{
    Dri_USART1_Start();
}
/**
 * @brief 结束函数
 * 
 */
void App_Commucation_Stop(void)
{
    Dri_USART1_Stop();
}

void App_Commucation_CommandProcess(uint16_t *rate, uint16_t *duration)
{
    while(!isRecSussed);
    *rate = atoi((char *)recRete);
    *duration = atoi((char *)recDura);
}
uint8_t sendBuf[10] = {0};
void App_Commucation_SendData(uint16_t data)
{
    sprintf((char *)sendBuf, "%d", data);
    Dri_USART1_SendStr(sendBuf, strlen((char *)sendBuf));
}
