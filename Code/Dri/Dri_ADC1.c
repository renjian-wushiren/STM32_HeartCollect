#include "Dri_ADC1.h"
/**
 * @brief ADC1�ĳ�ʼ������
 */
void Dri_ADC1_Init(void)
{
    // ���ö�Ӧ��ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // ʹ��ADC1ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // ���ö�Ӧ���ŵĹ���ģʽ(ģ������CNF00 MODE00)
    GPIOC->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
    // ADC��ص�����
    /*
        1.����ɨ��ģʽ,ֻ��һ��ͨ������Ҫɨ��ģʽ
        2.��������ת��ģʽ
        3.�������ݶ��뷽ʽ(�����,�Ҷ���,Ĭ�����Ҷ���)
        4.���ò���ʱ�� 010 13.5����
        5.����ͨ����(����ͨ����,ע��ͨ����)
        6.�����������ģʽ
    */
    // ����ɨ��ģʽ
    ADC1->CR1 &= ~ADC_CR1_SCAN;
    // ����ADC1��CR2�Ĵ�����CONTλ��ʹADC1��������ת��ģʽ
    ADC1->CR2 |= ADC_CR2_CONT;
    // ����ADC1��CR2�Ĵ�����ALIGNλ��ʹADC1��ת������Ҷ���
    ADC1->CR2 &= ~ADC_CR2_ALIGN;
    // ����ADC1��SMPR1�Ĵ�����SMP10[2:0]λ��ʹADC1��ת��ʱ�䰴��13.5���ڽ���
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP12_2 | ADC_SMPR1_SMP12_0);
    ADC1->SMPR1 |= ADC_SMPR1_SMP12_1;
    // ����ADC1��SQR1�Ĵ�����L[3:0]λ������ADC1�Ĺ���ͨ�����г���Ϊ1��ת��
    ADC1->SQR1 &= ~ADC_SQR1_L;
    // �������,��SQR3�Ĵ�����������
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= 12; // ����Ϊͨ��12
    // ����CR2�Ĵ���,��������Ϊ�����������ת������ͨ��
    ADC1->CR2 |= ADC_CR2_EXTSEL;
    // ���ù�������ⲿת��
    ADC1->CR2 &= ~ADC_CR2_EXTTRIG;
}
/**
 * @brief ADC ��������
 */
void Dri_ADC1_Start(void)
{
    // �ϵ�,ʹ��ADC������ģʽ����
    ADC1->CR2 |= ADC_CR2_ADON;
    // ִ��У׼
    ADC1->CR2 |= ADC_CR2_CAL;
    // �ȴ�У׼���
    while (ADC1->CR2 & ADC_CR2_CAL)
        ;
    // ����ת��
    ADC1->CR2 |= ADC_CR2_ADON;
    // �������ת��
    ADC1->CR2 |= ADC_CR2_SWSTART;
    // �ȴ�ת�����
    while (!(ADC1->SR & ADC_SR_EOC))
        ;
}
/**
 * @brief ADC1��ֹͣ����
 *
 */
void Dri_ADC1_Stop(void)
{
    ADC1->CR2 &= ~ADC_CR2_ADON;
}
/**
 * @brief ��ȡADC1ת�����ĵ�ѹֵ
 */
uint16_t Dri_ADC1_GetValue(void)
{
    return ADC1->DR;
}