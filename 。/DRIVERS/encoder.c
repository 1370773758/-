#include "encoder.h"

/*tim8 ch1:c6 ch2:c7 编码器 */

void encoder(uint32_t psc1,uint32_t arr1)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//配置时基
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	//TIM向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period = arr1;
	//配置自动重装载寄存器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc1;
	//配置定时器时钟分频
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	//时钟分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	//重复计数器无效0
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	
	//配置输入
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	//输入器不分频
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	//上升沿捕获
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	//映射到IC1
	TIM_ICInitStruct.TIM_ICFilter = 0;
	//不滤波
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICFilter = 0;
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	//使能编码器模式3 0x0003
	  TIM4 -> CNT = 0;
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	//TIM_SetCounter(TIM4,0);
	
	TIM_Cmd(TIM4, ENABLE);
}

int Read_Encoder(u8 TIMX)   
{
   int Encoder_TIM;    
   switch(TIMX)
	 {
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT ;break;

		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;    /*CNT清零*/
}
