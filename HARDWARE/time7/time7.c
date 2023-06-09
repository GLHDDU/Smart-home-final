#include "time7.h"
#include "stm32f10x.h"  //包含需要的头文件






void TIM7_Config(unsigned short int arr, unsigned short int psc)
{
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //使能TIM6时钟


/*基础设置*/
TIM_TimeBaseStructure.TIM_Period = arr;//计数值10000   
TIM_TimeBaseStructure.TIM_Prescaler = psc;    //预分频,此值+1为分频的除数
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //采样分频
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

TIM_ClearITPendingBit(TIM7,TIM_IT_Update);                    //清除溢出中断标志位
TIM_ITConfig(TIM7,TIM_IT_Update, ENABLE);     //使能TIM6中断
TIM_Cmd(TIM7, ENABLE);     //使能定时器6
}
/**********************************************************
** 函数名:NVIC_Config
** 功能描述:  中断优先级配置
** 输入参数: 无
** 输出参数: 无
***********************************************************/
void NVICTIM7_Config(void)
{
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //采用组别2 
 
NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;//TIM6中断
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//占先式优先级设置为0
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //副优先级设置为0
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断使能
NVIC_Init(&NVIC_InitStructure);//中断初始化
}

