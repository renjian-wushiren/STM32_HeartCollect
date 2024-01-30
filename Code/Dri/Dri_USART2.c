#include "Dri_USART2.h"
#include "Debug.h"
void Dri_USART2_Init(void)
{
    //开启对应时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  //使能GPIOA时钟
    RCC->APB2ENR |= RCC_APB1ENR_USART2EN;  //使能USART2时钟
    //配置对应引脚的模式PA2推挽输出,PA3浮空输入
    GPIOA->CRL |= (GPIO_CRL_MODE2 | GPIO_CRL_CNF2_1);
    GPIOA->CRL |= GPIO_CRL_CNF3_0;
    USART2->BRR = 0x271;//配置波特率
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);//使能接受与发送
    USART2->CR1 |= USART_CR1_RXNEIE;//使能接收中断
    USART2->CR1 |= USART_CR1_IDLEIE;//使能空闲中断
    //配置NVIC
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART2_IRQn, 0);
    NVIC_EnableIRQ(USART2_IRQn);
}

void Dri_USART2_Start(void)
{
    USART2->CR1 |= USART_CR1_UE; //开启USART2
}

void Dri_USART2_Stop(void)
{
    USART2->CR1 &= ~USART_CR1_UE; //关闭USART2
}

uint8_t Dri_USART2_ReceiveChar(void)
{
    while(!(USART2->SR & USART_SR_RXNE)); //等待接收到数据
    return USART2->DR; //返回接收到的数据
}

void Dri_USART2_SendChar(uint8_t c)
{
    while(!(USART2->SR & USART_SR_TXE)); //等待发送缓冲区为空
    USART2->DR = c; //发送数据
}

void Dri_USART2_SendString(uint8_t *str, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++){ //循环发送字符串中的每个字符
        Dri_USART2_SendChar(str[i]); //发送字符
    }
}
/**
 * @brief 自定义的回调服务函数
 * 
 * @param buf 缓冲区数组
 * @param len 缓冲区长度
 * @return __weak 弱函数,当被重写时执行重写的函数,不被重写的时候执行本函数
 */
__weak void Dri_USART2_CallBack(uint8_t buf[], uint8_t len){

}

uint8_t buf[100] = {0};
uint8_t len = 0;
void USART2_IRQHandler(void){
    if(USART2->SR & USART_SR_RXNE){ //接收到数据
        uint8_t data = USART2->DR; //读取接收到的数据
        buf[len++] = data; //将数据存入缓冲区
    }else{
        //清除中断标志位
        USART2->SR;
        USART2->DR;
        //处理接收到的数据
        Dri_USART2_CallBack(buf, len);
        len = 0; //重置缓冲区长度
    }
}
