#include "tim.h"
/* 定时器中断使led灯5s闪烁*/
void tim6_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef tim_init;
	
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM6,ENABLE );
	
	tim_init .TIM_Period =arr;
	tim_init .TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM6 ,&tim_init);
	
	TIM_ClearFlag (TIM6,TIM_FLAG_Update);
	TIM_ITConfig (TIM6,TIM_IT_Update,ENABLE );
	nvic_cfg (TIM6_IRQn,2,0);
	TIM_Cmd (TIM6,ENABLE );
}

void tim7_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
	/* 配置时基结构体 */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	//使能定时器时钟
  
	TIM_TimeBaseStructure.TIM_Prescaler = psc;   
	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Period = arr;         
	//配置自动重装载寄存器的值
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	//初始化TIM6时间基数单位

	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	//清除更新中断，防止一打开中断立马产生中断
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	//打开定时器更新中断

	nvic_cfg(TIM7_IRQn, 1, 0);
	/*配置中断优先级*/
	TIM_Cmd(TIM7, ENABLE);
	//使能定时器
}
