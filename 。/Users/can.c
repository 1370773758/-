#include "can.h"
/* can 通讯实验 */
u8 flag=0;



void can_cfg(void)
{
	GPIO_InitTypeDef      gpio_init;
	CAN_InitTypeDef       can_init;
	CAN_FilterInitTypeDef can_filterinit;
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE );
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_CAN1 ,ENABLE);
	
	gpio_init.GPIO_Pin=GPIO_Pin_11;
	gpio_init.GPIO_Mode=GPIO_Mode_AF_PP ;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init);
	
	gpio_init.GPIO_Pin=GPIO_Pin_12;
	gpio_init.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA ,&gpio_init);
	
	//can单元设置 配置工作模式
	can_init.CAN_Mode=CAN_Mode_Normal;//回环模式，测试完后改为普通模式
	can_init.CAN_TTCM=DISABLE;			//非时间触发通信模式  
	can_init.CAN_ABOM=ENABLE;			//软件自动离线管理	 
	can_init.CAN_AWUM=ENABLE;			//睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	can_init.CAN_NART=ENABLE;			//报文错误自动传送 
	can_init.CAN_RFLM=ENABLE;		 	//报文不锁定,新的覆盖旧的  
	can_init.CAN_TXFP=DISABLE;			//优先级由报文标识符决定 
	//设置波特率 1Mbps SYNC_SE段固定是1Tq
	can_init.CAN_SJW=CAN_SJW_1tq;
	can_init.CAN_BS1=CAN_BS1_5tq;
	can_init.CAN_BS2=CAN_BS2_3tq;//bs1+bs2+se段=9Tq
	can_init.CAN_Prescaler=4;//内部会自减1
	CAN_Init(CAN1 ,&can_init);
/* can过滤器 */
	can_filterinit.CAN_FilterActivation=ENABLE; //是否使能过滤器
	can_filterinit.CAN_FilterFIFOAssignment=CAN_FilterFIFO0;//数据存入FIFO0
	can_filterinit.CAN_FilterNumber=0;//0到13
	can_filterinit.CAN_FilterScale=CAN_FilterScale_32bit;//16位 32位
	can_filterinit.CAN_FilterMode=CAN_FilterMode_IdMask;
	/* 过滤的是扩展帧、扩展数据帧 */
	can_filterinit.CAN_FilterIdHigh=0x0000;//((PASS_ID<<3|CAN_ID_EXT|CAN_RTR_Data)&0xFFFF0000)>>16;//过滤的ID
	can_filterinit.CAN_FilterIdLow=0x0000;//((PASS_ID<<3|CAN_ID_EXT|CAN_RTR_Data)&0xFFFF);
	/*扩展数据帧的低16位，不需要位移 */
	can_filterinit.CAN_FilterMaskIdHigh=0x01E0;//0xFFFF;//32位MASK
	can_filterinit.CAN_FilterMaskIdLow=0x0000;//0xFFFF;//不正常的配置
	CAN_FilterInit(&can_filterinit);			//滤波器初始化

	nvic_cfg (USB_LP_CAN1_RX0_IRQn,1,1);//接收邮箱0
	/*中断函数错的话 会卡在启动文件*/
	CAN_ITConfig (CAN1 ,CAN_IT_FMP0,ENABLE );//CAN_IT_FMP0接受邮箱0产生的中断,使能中断
	
	CAN_Receive(CAN1,CAN_FIFO0,&CAN_Rece_Data);
}
