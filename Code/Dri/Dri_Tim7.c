#include "Dri_TIM7.h"
#include "Debug.h"
/**
 * @description: 给定时器7进行初始化
 * @return {*}
 */
void Dri_TIM7_Init(void)
{
    /* 1. 给定时器6开启时钟*/
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

    /* 2. 设置预分频值: 分频值7199表示7200分频。分频后频率10K，周期100us */
    TIM7->PSC = 7200 - 1;

    /*
    3. 设置自动重转载寄存器的值，决定中断发生的频率。
        假设设置为9999，表示计数器计数10000次发生一次中断。
        计数一次100us，10次1000us，正好1ms
    */
    TIM7->ARR = 10 - 1;

    /* 为了避免一启动立即进入更新中断,可以先产生一个更新事件 */
    // TIM7->CR1 |= TIM_CR1_URS;
    TIM7->EGR |= TIM_EGR_UG; /* 预分频寄存器和重装载寄存器的值更新到影子寄存器 */
    TIM7->SR &= ~TIM_SR_UIF;
    
    /* 4. 使能更新中断 */
    TIM7->DIER |= TIM_DIER_UIE;

    /* NVIC配置 */
    /* 5. 设置中断优先级分组 */
    NVIC_SetPriorityGrouping(3);
    /* 6. 设置中断优先级 */
    NVIC_SetPriority(TIM7_IRQn, 1);

    /* 7. 使能定时器7的中断 */
    NVIC_EnableIRQ(TIM7_IRQn);

    
}

void Dri_TIM7_Start(void)
{
    //使能计数器
    TIM7->CR1 |= TIM_CR1_CEN;
}

void Dri_TIM7_Stop(void)
{
    //关闭计数器
    TIM7->CR1 &= ~TIM_CR1_CEN;
}
/**
 * @brief 定时器6的更新回调函数
 * 
 * @return __weak 
 */
__weak void TIM7_UpInterruptCallBuck(uint32_t mscount) {}
uint32_t mscount = 0;
/**
 * @description: TIM6的中断服务函数
 * @return {*}
 */
void TIM7_IRQHandler(void)
{
    TIM7->SR &= ~TIM_SR_UIF;
    mscount++;
    TIM7_UpInterruptCallBuck(mscount);
}
