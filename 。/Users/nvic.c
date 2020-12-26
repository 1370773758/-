#include "nvic.h"

void nvic_cfg(uint16_t IRQChannel, uint16_t MainPriority, uint16_t SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);

	//设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;      
	//设置主优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MainPriority;
	//设置抢占式优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;    
	//使能中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}
