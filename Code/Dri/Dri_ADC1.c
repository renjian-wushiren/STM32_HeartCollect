#include "Dri_ADC1.h"
/**
 * @brief ADC1的初始化方法
 */
void Dri_ADC1_Init(void)
{
    // 配置对应的时钟
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // 使能ADC1时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // 配置对应引脚的工作模式(模拟输入CNF00 MODE00)
    GPIOC->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
    // ADC相关的配置
    /*
        1.禁用扫描模式,只有一个通道不需要扫描模式
        2.启用连续转换模式
        3.设置数据对齐方式(左对齐,右对齐,默认是右对齐)
        4.设置采样时间 010 13.5周期
        5.配置通道组(规则通道组,注入通道组)
        6.设置软件触发模式
    */
    // 禁用扫描模式
    ADC1->CR1 &= ~ADC_CR1_SCAN;
    // 设置ADC1的CR2寄存器的CONT位，使ADC1进入连续转换模式
    ADC1->CR2 |= ADC_CR2_CONT;
    // 设置ADC1的CR2寄存器的ALIGN位，使ADC1的转换结果右对齐
    ADC1->CR2 &= ~ADC_CR2_ALIGN;
    // 设置ADC1的SMPR1寄存器的SMP10[2:0]位，使ADC1的转换时间按照13.5周期进行
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP12_2 | ADC_SMPR1_SMP12_0);
    ADC1->SMPR1 |= ADC_SMPR1_SMP12_1;
    // 设置ADC1的SQR1寄存器的L[3:0]位，设置ADC1的规则通道序列长度为1个转换
    ADC1->SQR1 &= ~ADC_SQR1_L;
    // 清零操作,将SQR3寄存器进行清零
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= 12; // 配置为通道12
    // 设置CR2寄存器,将其设置为软件启动开启转换规则通道
    ADC1->CR2 |= ADC_CR2_EXTSEL;
    // 禁用规则组的外部转换
    ADC1->CR2 &= ~ADC_CR2_EXTTRIG;
}
/**
 * @brief ADC 启动函数
 */
void Dri_ADC1_Start(void)
{
    // 上电,使得ADC从休眠模式唤醒
    ADC1->CR2 |= ADC_CR2_ADON;
    // 执行校准
    ADC1->CR2 |= ADC_CR2_CAL;
    // 等待校准完成
    while (ADC1->CR2 & ADC_CR2_CAL)
        ;
    // 启动转换
    ADC1->CR2 |= ADC_CR2_ADON;
    // 启用软件转换
    ADC1->CR2 |= ADC_CR2_SWSTART;
    // 等待转换完成
    while (!(ADC1->SR & ADC_SR_EOC))
        ;
}
/**
 * @brief ADC1的停止函数
 *
 */
void Dri_ADC1_Stop(void)
{
    ADC1->CR2 &= ~ADC_CR2_ADON;
}
/**
 * @brief 获取ADC1转换到的电压值
 */
uint16_t Dri_ADC1_GetValue(void)
{
    return ADC1->DR;
}