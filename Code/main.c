#include "Debug.h"
#include "App_Commucation.h"
#include "App_HeartColler.h"
extern uint8_t isToReadAdcV;
int main()
{
    App_Commucation_Init();
    App_Commucation_Start();
    debug_init();
    debug_printfln("��ʼһ��");
    uint16_t rate,duration;
    App_Commucation_CommandProcess(&rate,&duration);
    APP_HeartCollect_Start(rate,duration);
    while (1) {
        uint16_t heartData = APP_HeartCollect_ReadHeartData();
        App_Commucation_SendData(heartData);
    }
}
