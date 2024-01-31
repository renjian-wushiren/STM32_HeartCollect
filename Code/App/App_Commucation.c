#include "App_Commucation.h"
#include "Debug.h"
#include <string.h>
uint8_t recRete[10] = {0}; // ���ղ�����
uint8_t recDura[10] = {0}; // ���ղ���ʱ��
uint8_t isRecSussed = 0;   // �Ƿ���ճɹ�
/**
 * @brief 
 *
 * @param buf ��������
 * @param len ����
 */
void USART1_Callback(uint8_t buff[], uint8_t len)
{
    if (buff[0] == 's') { 
        memcpy(recRete, &buff[1], len - 2);
    } else if (buff[0] == 'c') { // ???????��????????
        memcpy(recDura, &buff[1], len - 2);
        isRecSussed = 1;
    }
}
/**
 * @brief ��ʼ��
 * 
 */
void App_Commucation_Init(void)
{
    Dri_USART1_Init();
}
/**
 * @brief ��ʼ����
 * 
 */
void App_Commucation_Start(void)
{
    Dri_USART1_Start();
}
/**
 * @brief ��������
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
