#include "Debug.h"
#include "App_Commucation.h"
#include "App_HeartColler.h"
int main()
{
    App_Commucation_Init();
    App_Commucation_Start();
    debug_init();
    debug_printfln("开始一把");
    uint16_t rate,duration;
    App_Commucation_CommandProcess(&rate,&duration);
    debug_printfln("rate = %d,duration = %d",rate,duration);
    APP_HeartCollect_Start(rate,duration);
    while (1) {
        uint16_t heartData = APP_HeartCollect_ReadHeartData();
        // debug_printfln("heartData = %d",heartData);
        App_Commucation_SendData(heartData);
    }
}
