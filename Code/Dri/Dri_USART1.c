#include "Dri_USART1.h"

void Dri_USART1_Init()
{
    /*�������ŵ�ʱ��*/
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    /*���ڵ�ʱ��*/
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    GPIOA->CRH |= GPIO_CRH_CNF9_1; 
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOA->CRH |= GPIO_CRH_MODE9;

    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    /*�����ʵ�����*/
    USART1->BRR |= 0x271;
    /*����8������*/
    USART1->CR1 &= ~USART_CR1_M;
    /*����Ҫ����λ*/
    USART1->CR1 &= ~USART_CR1_PCE;
    /*��ֹλ��һ��bit*/
    USART1->CR2 &= ~USART_CR2_STOP;
    /*���ڷ���ʹ��*/
    USART1->CR1 |= USART_CR1_TE;
    /*������ȡʹ��*/
    USART1->CR1 |= USART_CR1_RE;


    /*����ȫ�����ж�*/

    /*�յ�һ���ֽڵ��ж�*/
    USART1->CR1 |= USART_CR1_RXNEIE;

    /*�鿴���հ�֡���ж�*/
    USART1->CR1 |= USART_CR1_IDLEIE;


    NVIC_SetPriorityGrouping(3);

    NVIC_SetPriority(USART1_IRQn, 2);

    /*ȫ�����ж�����nvic���ġ�*/
    NVIC_EnableIRQ(USART1_IRQn);

    
}
void Dri_USART1_Start(void){
    /*����ʹ��*/
    USART1->CR1 |= USART_CR1_UE;
}
void Dri_USART1_Stop(void){
    /*����ʹ��*/
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
    /*�����Ƿ������ǿյ�,���ж�*/
    while ((USART1->SR & USART_SR_RXNE) == 0)
        ;
    return USART1->DR;
}


void Dri_USART1_ReceiveStr(uint8_t *str, uint8_t *len)
{
    uint8_t i = 0;
    while (1) {
        /*��û���յ�����֮ǰ���Ͳ��ϼ���Ƿ��ǿ��е�*/

        while ((USART1->SR & USART_SR_RXNE) == 0) {
            if (USART1->SR & USART_SR_IDLE) {
                return;
            }
        }

        /*��������ݵĻ��ͷ���*/
        str[i] = USART1->DR;
        i++;
        *len = i;
    }
}

__weak void USART1_Callback(uint8_t buff[], uint8_t len) {}

uint8_t buff[100] = {0};
uint8_t len       = 0;
/*�жϺ���
���жϺ�����������е���ȡ�ͷ���*/
void USART1_IRQHandler(void)
{
    if ((USART1->SR & USART_SR_RXNE)) {
        buff[len] = USART1->DR; // ��λ��־λ
        len++;

    } else if ((USART1->SR & USART_SR_IDLE)) {
        /*���е�ʱ�򣬾ͷ�������ˣ����ʱ�����Ҫ������,��Ҫ��λ��־λ*/
        USART1->SR;
        USART1->DR;//�����жϱ�־λ

        /*�������յ�������*/
        USART1_Callback(buff, len);
        len = 0;
    }
}

/*�ض���printf()����Ϊprintf()�ײ��ǵ�����fputc���õ�*/

int fputc(int ch, FILE *file)
{
    Dri_USART1_Sendchar((uint8_t)ch);
    return ch;
}

