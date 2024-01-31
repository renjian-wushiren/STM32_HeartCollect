#include "Dri_USART2.h"
#include "Debug.h"
void Dri_USART2_Init(void)
{
    //������Ӧʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  //ʹ��GPIOAʱ��
    RCC->APB2ENR |= RCC_APB1ENR_USART2EN;  //ʹ��USART2ʱ��
    //���ö�Ӧ���ŵ�ģʽPA2�������,PA3��������
    GPIOA->CRL |= (GPIO_CRL_MODE2 | GPIO_CRL_CNF2_1);
    GPIOA->CRL |= GPIO_CRL_CNF3_0;
    USART2->BRR = 0x271;//���ò�����
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);//ʹ�ܽ����뷢��
    USART2->CR1 |= USART_CR1_RXNEIE;//ʹ�ܽ����ж�
    USART2->CR1 |= USART_CR1_IDLEIE;//ʹ�ܿ����ж�
    //����NVIC
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART2_IRQn, 0);
    NVIC_EnableIRQ(USART2_IRQn);
}

void Dri_USART2_Start(void)
{
    USART2->CR1 |= USART_CR1_UE; //����USART2
}

void Dri_USART2_Stop(void)
{
    USART2->CR1 &= ~USART_CR1_UE; //�ر�USART2
}

uint8_t Dri_USART2_ReceiveChar(void)
{
    while(!(USART2->SR & USART_SR_RXNE)); //�ȴ����յ�����
    return USART2->DR; //���ؽ��յ�������
}

void Dri_USART2_SendChar(uint8_t c)
{
    while(!(USART2->SR & USART_SR_TXE)); //�ȴ����ͻ�����Ϊ��
    USART2->DR = c; //��������
}

void Dri_USART2_SendString(uint8_t *str, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++){ //ѭ�������ַ����е�ÿ���ַ�
        Dri_USART2_SendChar(str[i]); //�����ַ�
    }
}
/**
 * @brief �Զ���Ļص�������
 * 
 * @param buf ����������
 * @param len ����������
 * @return __weak ������,������дʱִ����д�ĺ���,������д��ʱ��ִ�б�����
 */
__weak void Dri_USART2_CallBack(uint8_t buf[], uint8_t len){

}

uint8_t buf[100] = {0};
uint8_t len = 0;
void USART2_IRQHandler(void){
    if(USART2->SR & USART_SR_RXNE){ //���յ�����
        uint8_t data = USART2->DR; //��ȡ���յ�������
        buf[len++] = data; //�����ݴ��뻺����
    }else{
        //����жϱ�־λ
        USART2->SR;
        USART2->DR;
        //������յ�������
        Dri_USART2_CallBack(buf, len);
        len = 0; //���û���������
    }
}
