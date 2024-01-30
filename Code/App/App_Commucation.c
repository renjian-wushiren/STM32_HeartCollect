#include "App_Commucation.h"
<<<<<<< HEAD
#include "Debug.h"
=======
#include "Debug.h"
#include <string.h>
uint8_t recRete[10] = {0}; // 用于接收采样率
uint8_t recDura[10] = {0}; // 用于接收采样时间
uint8_t isRecSussed = 0;   // 接收是否完成的标志
/**
 * @brief 重写USART1的回调函数
 *
 * @param buf 缓冲区数组
 * @param len 缓冲区长度
 */
void USART1_Callback(uint8_t buff[], uint8_t len)
{
    if (buff[0] == 's') { // 采样率接收完毕
        memcpy(recRete, &buff[1], len - 2);
    } else if (buff[0] == 'c') { // 采样时长接收完毕
        memcpy(recDura, &buff[1], len - 2);
        isRecSussed = 1;
    }
}
/**
 * @brief 上位机与下位机的通讯初始化
 * 
 */
void App_Commucation_Init(void)
{
    Dri_USART1_Init();
}
/**
 * @brief 上位机与下位机的通讯开始
 * 
 */
void App_Commucation_Start(void)
{
    Dri_USART1_Start();
}
/**
 * @brief 上位机与下位机的通讯结束
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
>>>>>>> 994a28c (姘磋川妫�娴嬮」鐩�)
