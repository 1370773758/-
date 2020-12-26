#include "BSP.h"
//定义外部结构体变量，该结构体变量为发送结构体，名称：chassis_one_motor_txm
/*****************************************
//Author     :JasonLin
//Version	   :V2.0			 Ownership-Reserved
//Date       :2015/3/15
//Description:MCIO Board support package  
*****************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组2 两位抢占（0-3）  两位响应（0-3）=

	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  
	///////////////////////////////////////CAN			0 1
	

  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);



  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; 	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	

 
 /*优先级分组：优先级分组是为了给抢占式优先级和响应优先级在中断优先级寄存器的高四位分配各自所占的位数
               在同一个程序中优先级分组只能设定一次 */

 /*抢占优先级: 当一个中断正在执行而另一个具有更高抢占优先级的中断到来时，抢占优先级高的就会抢占CPU处理权
 			         此时两个中断就属于嵌套中断关系，具有相同抢占优先级的中断没有嵌套关系*/

 /*响应优先级：即副优先级，当两个抢占优先级相同的中断同时到来，具有响应优先级高的中断优先获得CPU的处理权
               如果中断不是同时到来，则后来的要等待正在执行的中断处理完才能获得响应*/

}



//CAN总线定义
//************************************************************



/*
 * 函数名：Can_chassis_one_motor_gpio_conf
 * 描述  ：CAN的GPIO 配置,PB8上拉输入，PB9推挽输出
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void Can_chassis_one_motor_gpio_conf(void)
{
 	GPIO_InitTypeDef Can_chassis_one_motor_gpio;
   	
  	/*外设时钟设置*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

  	/*IO设置*/
	 // GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	/* Configure CAN pin: RX */									               // PB8
    Can_chassis_one_motor_gpio.GPIO_Pin = GPIO_Pin_11;
    Can_chassis_one_motor_gpio.GPIO_Mode = GPIO_Mode_IPU;	             // 上拉输入
    Can_chassis_one_motor_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &Can_chassis_one_motor_gpio);
    /* Configure CAN pin: TX */									               // PB9
    Can_chassis_one_motor_gpio.GPIO_Pin = GPIO_Pin_12;
    Can_chassis_one_motor_gpio.GPIO_Mode = GPIO_Mode_AF_PP;		         // 复用推挽输出
    Can_chassis_one_motor_gpio.GPIO_Speed = GPIO_Speed_50MHz;    
	  GPIO_Init(GPIOA, &Can_chassis_one_motor_gpio);
	
}

/*
 * 函数名：Can_chassis_one_motor_nvic_conf
 * 描述  ：CAN的NVIC 配置,第1优先级组，0，0优先级
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void Can_chassis_one_motor_nvic_conf(void)
{
   	  NVIC_InitTypeDef Can_chassis_one_motor_nvic;

	 	/*中断设置*/
	  Can_chassis_one_motor_nvic.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0中断
    Can_chassis_one_motor_nvic.NVIC_IRQChannelPreemptionPriority = 0;		   //抢占优先级0
    Can_chassis_one_motor_nvic.NVIC_IRQChannelSubPriority = 0;			   //子优先级为0
    Can_chassis_one_motor_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&Can_chassis_one_motor_nvic);
	
//			Can_chassis_one_motor_nvic.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
//      Can_chassis_one_motor_nvic.NVIC_IRQChannelPreemptionPriority = 0;
//      Can_chassis_one_motor_nvic.NVIC_IRQChannelSubPriority = 1;
//      Can_chassis_one_motor_nvic.NVIC_IRQChannelCmd = ENABLE;
//      NVIC_Init(&Can_chassis_one_motor_nvic);
}

/*
 * 函数名：Can_chassis_one_motor_init_conf
 * 描述  ：CAN的模式 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void Can_chassis_one_motor_init_conf(void)
{
   	  CAN_InitTypeDef        Can_chassis_one_motor_init;
	 	/************************CAN通信参数设置**********************************/
	  /*CAN寄存器初始化*/
	  CAN_DeInit(CAN1);
	  CAN_StructInit(&Can_chassis_one_motor_init);
	  /*CAN单元初始化*/
	  Can_chassis_one_motor_init.CAN_TTCM=DISABLE;			   //MCR-TTCM  关闭时间触发通信模式使能
      Can_chassis_one_motor_init.CAN_ABOM=ENABLE;			   //MCR-ABOM  自动离线管理 
      Can_chassis_one_motor_init.CAN_AWUM=ENABLE;			   //MCR-AWUM  使用自动唤醒模式
      Can_chassis_one_motor_init.CAN_NART=DISABLE;			   //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
      Can_chassis_one_motor_init.CAN_RFLM=DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
      Can_chassis_one_motor_init.CAN_TXFP=DISABLE;			   //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符 
      Can_chassis_one_motor_init.CAN_Mode = CAN_Mode_Normal;  //正常工作模式
      Can_chassis_one_motor_init.CAN_SJW=CAN_SJW_1tq;		   //BTR-SJW 重新同步跳跃宽度 2个时间单元
      Can_chassis_one_motor_init.CAN_BS1=CAN_BS1_5tq;		   //BTR-TS1 时间段1 占用了6个时间单元
      Can_chassis_one_motor_init.CAN_BS2=CAN_BS2_3tq;		   //BTR-TS1 时间段2 占用了3个时间单元
      Can_chassis_one_motor_init.CAN_Prescaler =4;		   ////BTR-BRP 波特率分频器  定义了时间单元的时间长度 36/(1+6+3)/4=0.8Mbps
	  CAN_Init(CAN1, &Can_chassis_one_motor_init);
}

/*
 * 函数名：Can_chassis_one_motor_filter_conf
 * 描述  ：CAN的过滤器 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void Can_chassis_one_motor_filter_conf(void)
{
    CAN_FilterInitTypeDef  Can_chassis_one_motor_filter;

	/*CAN过滤器初始化*/
	Can_chassis_one_motor_filter.CAN_FilterNumber=0;						//过滤器组0
    Can_chassis_one_motor_filter.CAN_FilterMode=CAN_FilterMode_IdMask;	//工作在标识符屏蔽位模式
	Can_chassis_one_motor_filter.CAN_FilterScale=CAN_FilterScale_32bit;	//过滤器位宽为单个32位。
	/* 使能报文标示符过滤器按照标示符的内容进行比对过滤，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
    Can_chassis_one_motor_filter.CAN_FilterIdHigh=0x0000; //(((u32)0x12<<21)&0xFFFF0000)>>16;				//要过滤的ID高位 
    Can_chassis_one_motor_filter.CAN_FilterIdLow= 0x0000; //(((u32)0x12<<21)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF; //要过滤的ID低位 
    Can_chassis_one_motor_filter.CAN_FilterMaskIdHigh= 0x01E0;			//过滤器高16位每位必须匹配
    Can_chassis_one_motor_filter.CAN_FilterMaskIdLow= 0x0000;			//过滤器低16位每位必须匹配
	Can_chassis_one_motor_filter.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0 ;				//过滤器被关联到FIFO0
	Can_chassis_one_motor_filter.CAN_FilterActivation=ENABLE;			//使能过滤器
	CAN_FilterInit(&Can_chassis_one_motor_filter);
	/*CAN通信中断使能*/
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
}


/*
 * 函数名：Can_chassis_one_motor_conf
 * 描述  ：完整配置CAN的功能
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void Can_chassis_one_motor_conf(void)
{
  Can_chassis_one_motor_gpio_conf();
  Can_chassis_one_motor_nvic_conf();
  Can_chassis_one_motor_init_conf();
  Can_chassis_one_motor_filter_conf();   
}


/*
 * 函数名：CAN_SetMsg
 * 描述  ：CAN通信报文内容设置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */	 
CanTxMsg CAN_SEND_MSG;
void CAN_SetMsg(char *data,char num,int CAN_ID)
{	  
	char circle;
  CAN_SEND_MSG.StdId=CAN_ID;						 
  CAN_SEND_MSG.IDE=CAN_ID_STD ;				//标准模式
  CAN_SEND_MSG.RTR=CAN_RTR_DATA;			//发送的是数据
  CAN_SEND_MSG.DLC=num;							//数据长度为2字节
	for(circle=0;circle<num;circle++)
	{
			CAN_SEND_MSG.Data[circle]=data[circle];
	}
	CAN_Transmit(CAN1,&CAN_SEND_MSG);
}
/**************************END OF FILE************************************/
//************************************************************

 
 
void TIM7_Configuration(void)//周期循环事件定时初始化
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = TIMPeriod-1;
  TIM_TimeBaseStructure.TIM_Prescaler =72-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;       
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);
   
  TIM_UpdateRequestConfig(TIM7,TIM_UpdateSource_Regular);
  TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM7,ENABLE);

}

//////////////////////////

void TIM_Configuration(void)//TIM初始化
{
	TIM7_Configuration();
}

void Led_Configuration(void)
{
	RCC->APB2ENR|=1<<2;
	RCC->APB2ENR|=1<<3;
	GPIOA->CRH&=0XFFF00FFF;
	GPIOA->CRH|=0X00033000;
	GPIOB->CRL&=0X0FFFFFFF;
	GPIOB->CRL|=0X30000000;
}

void ADC_Led_Configuration(void)
{
	RCC->APB2ENR|=1<<0;			//开启AFIO时钟
	RCC->APB2ENR|=1<<2;
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<4;
	RCC->APB2ENR|=1<<5;
	
	AFIO->MAPR&=~(7<<24);
	AFIO->MAPR|=2<<24;				//关闭JITA，开启SW
	
	GPIOA->CRH&=0X0FFFFFFF;
	GPIOA->CRH|=0X30000000;
	GPIOB->CRL&=0XFF000FFF;
	GPIOB->CRL|=0X00333000;
	GPIOB->CRH&=0X0000FFFF;
	GPIOB->CRH|=0X33330000;
	GPIOC->CRL&=0X00FFFFFF;
	GPIOC->CRL|=0X33000000;
	GPIOC->CRH&=0XFFF00000;
	GPIOC->CRH|=0X00033333;
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X33000300;
	//LED7=0;
	//LED1=0;
}

void KEY_Configuration(void)
{
	RCC->APB2ENR|=1<<2;
	GPIOA->CRH&=0XFFFFFFF0;
	GPIOA->CRH|=0X00000008;
	GPIOA->ODR|=1<<8;
}

//////SYSTICK 初始化

void Systick_Configuration(void)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8	9M
}

//////延时写入接口

void SysDelay_ms(u16 nms)//72M条件下,nms<=1864(2^24/9000)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*Sys_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01;           //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
}

void SysDelay_us(u32 nus)//72M条件下,nus<=2^24
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*Sys_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01;       //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}


///////Board Communication Package

u16 sbus_rx_buffer[16];

void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* config USART1 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3  | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	/* USART3 mode config */
	USART3->CR1|=1<<5;    //接收缓冲区非空中断使能	   
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx ;
	USART_Init(USART3, &USART_InitStructure); 
	USART_Cmd(USART3, ENABLE); 
}

void DMA_Config(void)
{
	RCC->AHBENR|=1<<0;			//开启DMA1时钟
	SysDelay_ms(5);				//等待DMA时钟稳定
	DMA1_Channel1->CPAR=(uint32_t)&(ADC1->DR); 	 	//DMA1 外设地址 
	DMA1_Channel1->CMAR=(uint32_t)sbus_rx_buffer; 	//DMA1,存储器地址
	DMA1_Channel1->CNDTR=16;    	//DMA1,传输数据量
	
	DMA1_Channel1->CCR|=0<<4;  		//从存储器读
	DMA1_Channel1->CCR|=1<<5;  		//普通模式
	DMA1_Channel1->CCR|=0<<6; 		//外设地址非增量模式
	DMA1_Channel1->CCR|=1<<7; 	 	//存储器增量模式
	DMA1_Channel1->CCR|=1<<8; 	 	//外设数据宽度为16位
	DMA1_Channel1->CCR|=1<<10; 		//存储器数据宽度16位
	DMA1_Channel1->CCR|=3<<12; 		//最高优先级
	DMA1_Channel1->CCR|=0<<14; 		//非存储器到存储器模式	 
	DMA1_Channel1->CCR|=1<<1;
	DMA1_Channel1->CCR|=1<<0;
}

void  Adc_Init(void)
{    
	//先初始化IO口
 	RCC->APB2ENR|=1<<2;    //使能PORTA口时钟 
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<4;
	GPIOA->CRL&=0X00000000;
	GPIOB->CRL&=0XFFFFFF00;
	GPIOC->CRL&=0XFF000000;
	RCC->APB2ENR|=1<<9;    //ADC1时钟使能	  
	RCC->APB2RSTR|=1<<9;   //ADC1复位
	RCC->APB2RSTR&=~(1<<9);//复位结束	    
	RCC->CFGR&=~(3<<14);   //分频因子清零	
	//SYSCLK/DIV2=12M ADC时钟设置为12M,ADC最大时钟不能超过14M!
	//否则将导致ADC准确度下降! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   //工作模式清零
	ADC1->CR1|=0<<16;      //独立工作模式   
	ADC1->CR1|=1<<8;    //扫描模式	 
	ADC1->CR2|=1<<1;    //连续转换模式
	ADC1->CR2&=~(1<<11);   //右对齐	 
	ADC1->SQR1=0x00F4A1EE;
	ADC1->SQR2=0x0E62916C;	//规则序列1 通道ch
	ADC1->SQR3=0x1A00886A;	//设置通道1的采样时间 
	ADC1->SMPR1&=0x00000000;
	ADC1->SMPR1|=0x00FFFFFF;
 	ADC1->SMPR2|=0x3FFFFFFF;     //239.5周期	 
	ADC1->CR2|=1<<0;	   //开启AD转换器	 
	ADC1->CR2|=1<<3;       //使能复位校准  
	while(ADC1->CR2&1<<3); //等待校准结束 			 
    //该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。 		 
	ADC1->CR2|=1<<2;        //开启AD校准	   
	while(ADC1->CR2&1<<2);  //等待校准结束
	//该位由软件设置以开始校准，并在校准结束时由硬件清除 
 
}				  

void BSP_Configuration(void)
{
    NVIC_Configuration();
		Adc_Init();
		DMA_Config();
		ADC_DMACmd(ADC1, ENABLE);
		ADC1->CR2|=1<<0;       //启动转换
		Led_Configuration();
		ADC_Led_Configuration();
		KEY_Configuration();
//		USART3_Config();
		Can_chassis_one_motor_conf();
    TIM_Configuration();
}


	 










