
#include "Util.h"

void Delay_us(uint16_t us)
{
    /* ��ʱ����װֵ */
    SysTick->LOAD = 72 * us;
    /* �����ǰ����ֵ */
    SysTick->VAL = 0;
    /*�����ڲ�ʱ��Դ��2λ->1��,����Ҫ�жϣ�1λ->0������������ʱ��(0λ->1)*/
    SysTick->CTRL = 0x5;
    /*�ȴ�������0�� ���������0��16λ����Ϊ1*/
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG))
        ;
    /* �رն�ʱ�� */
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
}

void Delay_ms(uint16_t ms)
{
    while (ms--) {
        Delay_us(1000);
    }
}

void Delay_s(uint16_t s)
{
    while (s--) {
        Delay_ms(1000);
    }
}
