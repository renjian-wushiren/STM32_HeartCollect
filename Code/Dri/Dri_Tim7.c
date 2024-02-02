#include "Dri_TIM7.h"
#include "Debug.h"
/**
 * @description: ����ʱ��7���г�ʼ��
 * @return {*}
 */
void Dri_TIM7_Init(void)
{
    /* 1. ����ʱ��6����ʱ��*/
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

    /* 2. ����Ԥ��Ƶֵ: ��Ƶֵ7199��ʾ7200��Ƶ����Ƶ��Ƶ��10K������100us */
    TIM7->PSC = 7200 - 1;

    /*
    3. �����Զ���ת�ؼĴ�����ֵ�������жϷ�����Ƶ�ʡ�
        ��������Ϊ9999����ʾ����������10000�η���һ���жϡ�
        ����һ��100us��10��1000us������1ms
    */
    TIM7->ARR = 10 - 1;

    /* Ϊ�˱���һ����������������ж�,�����Ȳ���һ�������¼� */
    // TIM7->CR1 |= TIM_CR1_URS;
    TIM7->EGR |= TIM_EGR_UG; /* Ԥ��Ƶ�Ĵ�������װ�ؼĴ�����ֵ���µ�Ӱ�ӼĴ��� */
    TIM7->SR &= ~TIM_SR_UIF;
    
    /* 4. ʹ�ܸ����ж� */
    TIM7->DIER |= TIM_DIER_UIE;

    /* NVIC���� */
    /* 5. �����ж����ȼ����� */
    NVIC_SetPriorityGrouping(3);
    /* 6. �����ж����ȼ� */
    NVIC_SetPriority(TIM7_IRQn, 1);

    /* 7. ʹ�ܶ�ʱ��7���ж� */
    NVIC_EnableIRQ(TIM7_IRQn);

    
}

void Dri_TIM7_Start(void)
{
    //ʹ�ܼ�����
    TIM7->CR1 |= TIM_CR1_CEN;
}

void Dri_TIM7_Stop(void)
{
    //�رռ�����
    TIM7->CR1 &= ~TIM_CR1_CEN;
}
/**
 * @brief ��ʱ��6�ĸ��»ص�����
 * 
 * @return __weak 
 */
__weak void TIM7_UpInterruptCallBuck(uint32_t mscount) {}
uint32_t mscount = 0;
/**
 * @description: TIM6���жϷ�����
 * @return {*}
 */
void TIM7_IRQHandler(void)
{
    TIM7->SR &= ~TIM_SR_UIF;
    mscount++;
    TIM7_UpInterruptCallBuck(mscount);
}
