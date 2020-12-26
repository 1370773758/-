#include "motor.h"

void Motor_Tim_Config(void)
{
	   GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	//	TIM_DeInit(TIM8);    
	/*将寄存器重新设置默认值*/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	//配置时基
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 7199;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);

	TIM_OCInitStruct.TIM_Pulse = 0;
	//初始化CCR（设置占空比）
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	//输出使能
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	//PWM工作模式
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	//输出高有效（起始波形高）

	/*初始化通道*/
	TIM_OC1Init(TIM8, &TIM_OCInitStruct);
	TIM_OC2Init(TIM8, &TIM_OCInitStruct);
    TIM_Cmd(TIM8, ENABLE);

	/*预装载使能*/
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	/*主输出使能*/
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	/*使能TIMx在ARR上预装载寄存器*/
}

void servo(void)//舵机
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM3_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	TIM_TimeBaseStructure.TIM_Period = 1999; 
	TIM_TimeBaseStructure.TIM_Prescaler =719; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
  TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE 主输出使能	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH4预装载使能	 	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM	
}
