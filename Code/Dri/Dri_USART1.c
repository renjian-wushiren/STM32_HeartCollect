#include "Dri_USART1.h"

void Dri_USART1_Init()
{
    /*两个引脚的时钟*/
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    /*串口的时钟*/
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    GPIOA->CRH |= GPIO_CRH_CNF9_1; 
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOA->CRH |= GPIO_CRH_MODE9;

    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    /*波特率的设置*/
    USART1->BRR |= 0x271;
    /*发送8个比特*/
    USART1->CR1 &= ~USART_CR1_M;
    /*不需要检验位*/
    USART1->CR1 &= ~USART_CR1_PCE;
    /*终止位是一个bit*/
    USART1->CR2 &= ~USART_CR2_STOP;
    /*串口发送使能*/
    USART1->CR1 |= USART_CR1_TE;
    /*串口收取使能*/
    USART1->CR1 |= USART_CR1_RE;


    /*串口全部的中断*/

    /*收到一个字节的中断*/
    USART1->CR1 |= USART_CR1_RXNEIE;

    /*查看到空白帧的中断*/
    USART1->CR1 |= USART_CR1_IDLEIE;


    NVIC_SetPriorityGrouping(3);

    NVIC_SetPriority(USART1_IRQn, 2);

    /*全部的中断是由nvic来的。*/
    NVIC_EnableIRQ(USART1_IRQn);

    
}
void Dri_USART1_Start(void){
    /*串口使能*/
    USART1->CR1 |= USART_CR1_UE;
}
void Dri_USART1_Stop(void){
    /*串口使能*/
    USART1->CR1 &= ~USART_CR1_UE;
}
void Dri_USART1_Sendchar(uint8_t byte)
{
    while ((USART1->SR & USART_SR_TXE) == 0)
        ;

    USART1->DR = byte;
}


void Dri_USART1_SendStr(uint8_t *str, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++) {
        Dri_USART1_Sendchar(str[i]);
    }
}


uint8_t Dri_USART1_ReceiveChar()
{
    /*看看是否里面是空的,用中断*/
    while ((USART1->SR & USART_SR_RXNE) == 0)
        ;
    return USART1->DR;
}


void Dri_USART1_ReceiveStr(uint8_t *str, uint8_t *len)
{
    uint8_t i = 0;
    while (1) {
        /*在没有收到数据之前，就不断检测是否是空闲的*/

        while ((USART1->SR & USART_SR_RXNE) == 0) {
            if (USART1->SR & USART_SR_IDLE) {
                return;
            }
        }

        /*如果有数据的话就返回*/
        str[i] = USART1->DR;
        i++;
        *len = i;
    }
}

__weak void USART1_Callback(uint8_t buff[], uint8_t len) {}

uint8_t buff[100] = {0};
uint8_t len       = 0;
/*中断函数
在中断函数中完成所有的收取和发送*/
void USART1_IRQHandler(void)
{
    if ((USART1->SR & USART_SR_RXNE)) {
        buff[len] = USART1->DR; // 复位标志位
        len++;

    } else if ((USART1->SR & USART_SR_IDLE)) {
        /*空闲的时候，就发送完毕了，这个时候就需要发送了,需要复位标志位*/
        USART1->SR;
        USART1->DR;//清零中断标志位

        /*发送所收到的数据*/
        USART1_Callback(buff, len);
        len = 0;
    }
}

/*重定向printf()，因为printf()底层是调用了fputc来用的*/

int fputc(int ch, FILE *file)
{
    Dri_USART1_Sendchar((uint8_t)ch);
    return ch;
}

