#include "App_Commucation.h"
<<<<<<< HEAD
#include "Debug.h"
=======
#include "Debug.h"
#include <string.h>
uint8_t recRete[10] = {0}; // ÓÃÓÚ½ÓÊÕ²ÉÑùÂÊ
uint8_t recDura[10] = {0}; // ÓÃÓÚ½ÓÊÕ²ÉÑùÊ±¼ä
uint8_t isRecSussed = 0;   // ½ÓÊÕÊÇ·ñÍê³ÉµÄ±êÖ¾
/**
 * @brief ÖØÐ´USART1µÄ»Øµ÷º¯Êý
 *
 * @param buf »º³åÇøÊý×é
 * @param len »º³åÇø³¤¶È
 */
void USART1_Callback(uint8_t buff[], uint8_t len)
{
    if (buff[0] == 's') { // ²ÉÑùÂÊ½ÓÊÕÍê±Ï
        memcpy(recRete, &buff[1], len - 2);
    } else if (buff[0] == 'c') { // ²ÉÑùÊ±³¤½ÓÊÕÍê±Ï
        memcpy(recDura, &buff[1], len - 2);
        isRecSussed = 1;
    }
}
/**
 * @brief ÉÏÎ»»úÓëÏÂÎ»»úµÄÍ¨Ñ¶³õÊ¼»¯
 * 
 */
void App_Commucation_Init(void)
{
    Dri_USART1_Init();
}
/**
 * @brief ÉÏÎ»»úÓëÏÂÎ»»úµÄÍ¨Ñ¶¿ªÊ¼
 * 
 */
void App_Commucation_Start(void)
{
    Dri_USART1_Start();
}
/**
 * @brief ÉÏÎ»»úÓëÏÂÎ»»úµÄÍ¨Ñ¶½áÊø
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
>>>>>>> 994a28c (æ°´è´¨æ£€æµ‹é¡¹ç›®)
