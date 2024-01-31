#include "Dri_TIM6.h"
#include "Debug.h"
/**
 * @description: ����ʱ��6���г�ʼ��
 * @return {*}
 */
void Dri_TIM6_Init(void)
{
    /* 1. ����ʱ��6����ʱ��*/
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    /* 2. ����Ԥ��Ƶֵ: ��Ƶֵ7199��ʾ7200��Ƶ����Ƶ��Ƶ��10K������100us */
    TIM6->PSC = 7200 - 1;

    /*
    3. �����Զ���ת�ؼĴ�����ֵ�������жϷ�����Ƶ�ʡ�
        ��������Ϊ9999����ʾ����������10000�η���һ���жϡ�
        ����һ��100us��10000��1000000us������1s
    */
    TIM6->ARR = 10 - 1;

    /* Ϊ�˱���һ����������������ж�,�����Ȳ���һ�������¼� */
    TIM6->CR1 |= TIM_CR1_URS;
    TIM6->EGR |= TIM_EGR_UG; /* Ԥ��Ƶ�Ĵ�������װ�ؼĴ�����ֵ���µ�Ӱ�ӼĴ��� */
    // TIM6->SR &= ~TIM_SR_UIF;
    
    /* 4. ʹ�ܸ����ж� */
    TIM6->DIER |= TIM_DIER_UIE;

    /* NVIC���� */
    /* 5. �����ж����ȼ����� */
    NVIC_SetPriorityGrouping(3);
    /* 6. �����ж����ȼ� */
    NVIC_SetPriority(TIM6_IRQn, 1);

    /* 7. ʹ�ܶ�ʱ��6���ж� */
    NVIC_EnableIRQ(TIM6_IRQn);

    
}

void Dri_TIM6_Start(void)
{
    //ʹ�ܼ�����
    TIM6->CR1 |= TIM_CR1_CEN;
}

void Dri_TIM6_Stop(void)
{
    //�رռ�����
    TIM6->CR1 &= ~TIM_CR1_CEN;
}
/**
 * @brief ��ʱ��6�ĸ��»ص�����
 * 
 * @return __weak 
 */
__weak void Dri_TIM6_UpInterruptCallBuck(void) {}

/**
 * @description: TIM6���жϷ�����
 * @return {*}
 */
void TIM6_IRQHandler(void)
{
    TIM6->SR &= ~TIM_SR_UIF;
    Dri_TIM6_UpInterruptCallBuck();
}
