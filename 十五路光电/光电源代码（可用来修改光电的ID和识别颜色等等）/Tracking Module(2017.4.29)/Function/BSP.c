#include "BSP.h"
//�����ⲿ�ṹ��������ýṹ�����Ϊ���ͽṹ�壬���ƣ�chassis_one_motor_txm
/*****************************************
//Author     :JasonLin
//Version	   :V2.0			 Ownership-Reserved
//Date       :2015/3/15
//Description:MCIO Board support package  
*****************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ���2 ��λ��ռ��0-3��  ��λ��Ӧ��0-3��=

	
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
	

 
 /*���ȼ����飺���ȼ�������Ϊ�˸���ռʽ���ȼ�����Ӧ���ȼ����ж����ȼ��Ĵ����ĸ���λ���������ռ��λ��
               ��ͬһ�����������ȼ�����ֻ���趨һ�� */

 /*��ռ���ȼ�: ��һ���ж�����ִ�ж���һ�����и�����ռ���ȼ����жϵ���ʱ����ռ���ȼ��ߵľͻ���ռCPU����Ȩ
 			         ��ʱ�����жϾ�����Ƕ���жϹ�ϵ��������ͬ��ռ���ȼ����ж�û��Ƕ�׹�ϵ*/

 /*��Ӧ���ȼ����������ȼ�����������ռ���ȼ���ͬ���ж�ͬʱ������������Ӧ���ȼ��ߵ��ж����Ȼ��CPU�Ĵ���Ȩ
               ����жϲ���ͬʱ�������������Ҫ�ȴ�����ִ�е��жϴ�������ܻ����Ӧ*/

}



//CAN���߶���
//************************************************************



/*
 * ��������Can_chassis_one_motor_gpio_conf
 * ����  ��CAN��GPIO ����,PB8�������룬PB9�������
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void Can_chassis_one_motor_gpio_conf(void)
{
 	GPIO_InitTypeDef Can_chassis_one_motor_gpio;
   	
  	/*����ʱ������*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

  	/*IO����*/
	 // GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	/* Configure CAN pin: RX */									               // PB8
    Can_chassis_one_motor_gpio.GPIO_Pin = GPIO_Pin_11;
    Can_chassis_one_motor_gpio.GPIO_Mode = GPIO_Mode_IPU;	             // ��������
    Can_chassis_one_motor_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &Can_chassis_one_motor_gpio);
    /* Configure CAN pin: TX */									               // PB9
    Can_chassis_one_motor_gpio.GPIO_Pin = GPIO_Pin_12;
    Can_chassis_one_motor_gpio.GPIO_Mode = GPIO_Mode_AF_PP;		         // �����������
    Can_chassis_one_motor_gpio.GPIO_Speed = GPIO_Speed_50MHz;    
	  GPIO_Init(GPIOA, &Can_chassis_one_motor_gpio);
	
}

/*
 * ��������Can_chassis_one_motor_nvic_conf
 * ����  ��CAN��NVIC ����,��1���ȼ��飬0��0���ȼ�
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void Can_chassis_one_motor_nvic_conf(void)
{
   	  NVIC_InitTypeDef Can_chassis_one_motor_nvic;

	 	/*�ж�����*/
	  Can_chassis_one_motor_nvic.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0�ж�
    Can_chassis_one_motor_nvic.NVIC_IRQChannelPreemptionPriority = 0;		   //��ռ���ȼ�0
    Can_chassis_one_motor_nvic.NVIC_IRQChannelSubPriority = 0;			   //�����ȼ�Ϊ0
    Can_chassis_one_motor_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&Can_chassis_one_motor_nvic);
	
//			Can_chassis_one_motor_nvic.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
//      Can_chassis_one_motor_nvic.NVIC_IRQChannelPreemptionPriority = 0;
//      Can_chassis_one_motor_nvic.NVIC_IRQChannelSubPriority = 1;
//      Can_chassis_one_motor_nvic.NVIC_IRQChannelCmd = ENABLE;
//      NVIC_Init(&Can_chassis_one_motor_nvic);
}

/*
 * ��������Can_chassis_one_motor_init_conf
 * ����  ��CAN��ģʽ ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void Can_chassis_one_motor_init_conf(void)
{
   	  CAN_InitTypeDef        Can_chassis_one_motor_init;
	 	/************************CANͨ�Ų�������**********************************/
	  /*CAN�Ĵ�����ʼ��*/
	  CAN_DeInit(CAN1);
	  CAN_StructInit(&Can_chassis_one_motor_init);
	  /*CAN��Ԫ��ʼ��*/
	  Can_chassis_one_motor_init.CAN_TTCM=DISABLE;			   //MCR-TTCM  �ر�ʱ�䴥��ͨ��ģʽʹ��
      Can_chassis_one_motor_init.CAN_ABOM=ENABLE;			   //MCR-ABOM  �Զ����߹��� 
      Can_chassis_one_motor_init.CAN_AWUM=ENABLE;			   //MCR-AWUM  ʹ���Զ�����ģʽ
      Can_chassis_one_motor_init.CAN_NART=DISABLE;			   //MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
      Can_chassis_one_motor_init.CAN_RFLM=DISABLE;			   //MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���  
      Can_chassis_one_motor_init.CAN_TXFP=DISABLE;			   //MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ�� 
      Can_chassis_one_motor_init.CAN_Mode = CAN_Mode_Normal;  //��������ģʽ
      Can_chassis_one_motor_init.CAN_SJW=CAN_SJW_1tq;		   //BTR-SJW ����ͬ����Ծ��� 2��ʱ�䵥Ԫ
      Can_chassis_one_motor_init.CAN_BS1=CAN_BS1_5tq;		   //BTR-TS1 ʱ���1 ռ����6��ʱ�䵥Ԫ
      Can_chassis_one_motor_init.CAN_BS2=CAN_BS2_3tq;		   //BTR-TS1 ʱ���2 ռ����3��ʱ�䵥Ԫ
      Can_chassis_one_motor_init.CAN_Prescaler =4;		   ////BTR-BRP �����ʷ�Ƶ��  ������ʱ�䵥Ԫ��ʱ�䳤�� 36/(1+6+3)/4=0.8Mbps
	  CAN_Init(CAN1, &Can_chassis_one_motor_init);
}

/*
 * ��������Can_chassis_one_motor_filter_conf
 * ����  ��CAN�Ĺ����� ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void Can_chassis_one_motor_filter_conf(void)
{
    CAN_FilterInitTypeDef  Can_chassis_one_motor_filter;

	/*CAN��������ʼ��*/
	Can_chassis_one_motor_filter.CAN_FilterNumber=0;						//��������0
    Can_chassis_one_motor_filter.CAN_FilterMode=CAN_FilterMode_IdMask;	//�����ڱ�ʶ������λģʽ
	Can_chassis_one_motor_filter.CAN_FilterScale=CAN_FilterScale_32bit;	//������λ��Ϊ����32λ��
	/* ʹ�ܱ��ı�ʾ�����������ձ�ʾ�������ݽ��бȶԹ��ˣ���չID�������µľ����������ǵĻ��������FIFO0�� */
    Can_chassis_one_motor_filter.CAN_FilterIdHigh=0x0000; //(((u32)0x12<<21)&0xFFFF0000)>>16;				//Ҫ���˵�ID��λ 
    Can_chassis_one_motor_filter.CAN_FilterIdLow= 0x0000; //(((u32)0x12<<21)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF; //Ҫ���˵�ID��λ 
    Can_chassis_one_motor_filter.CAN_FilterMaskIdHigh= 0x01E0;			//��������16λÿλ����ƥ��
    Can_chassis_one_motor_filter.CAN_FilterMaskIdLow= 0x0000;			//��������16λÿλ����ƥ��
	Can_chassis_one_motor_filter.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0 ;				//��������������FIFO0
	Can_chassis_one_motor_filter.CAN_FilterActivation=ENABLE;			//ʹ�ܹ�����
	CAN_FilterInit(&Can_chassis_one_motor_filter);
	/*CANͨ���ж�ʹ��*/
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
}


/*
 * ��������Can_chassis_one_motor_conf
 * ����  ����������CAN�Ĺ���
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void Can_chassis_one_motor_conf(void)
{
  Can_chassis_one_motor_gpio_conf();
  Can_chassis_one_motor_nvic_conf();
  Can_chassis_one_motor_init_conf();
  Can_chassis_one_motor_filter_conf();   
}


/*
 * ��������CAN_SetMsg
 * ����  ��CANͨ�ű�����������
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */	 
CanTxMsg CAN_SEND_MSG;
void CAN_SetMsg(char *data,char num,int CAN_ID)
{	  
	char circle;
  CAN_SEND_MSG.StdId=CAN_ID;						 
  CAN_SEND_MSG.IDE=CAN_ID_STD ;				//��׼ģʽ
  CAN_SEND_MSG.RTR=CAN_RTR_DATA;			//���͵�������
  CAN_SEND_MSG.DLC=num;							//���ݳ���Ϊ2�ֽ�
	for(circle=0;circle<num;circle++)
	{
			CAN_SEND_MSG.Data[circle]=data[circle];
	}
	CAN_Transmit(CAN1,&CAN_SEND_MSG);
}
/**************************END OF FILE************************************/
//************************************************************

 
 
void TIM7_Configuration(void)//����ѭ���¼���ʱ��ʼ��
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

void TIM_Configuration(void)//TIM��ʼ��
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
	RCC->APB2ENR|=1<<0;			//����AFIOʱ��
	RCC->APB2ENR|=1<<2;
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<4;
	RCC->APB2ENR|=1<<5;
	
	AFIO->MAPR&=~(7<<24);
	AFIO->MAPR|=2<<24;				//�ر�JITA������SW
	
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

//////SYSTICK ��ʼ��

void Systick_Configuration(void)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8	9M
}

//////��ʱд��ӿ�

void SysDelay_ms(u16 nms)//72M������,nms<=1864(2^24/9000)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*Sys_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01;           //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
}

void SysDelay_us(u32 nus)//72M������,nus<=2^24
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*Sys_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01;       //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
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
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	/* USART3 mode config */
	USART3->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	   
	
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
	RCC->AHBENR|=1<<0;			//����DMA1ʱ��
	SysDelay_ms(5);				//�ȴ�DMAʱ���ȶ�
	DMA1_Channel1->CPAR=(uint32_t)&(ADC1->DR); 	 	//DMA1 �����ַ 
	DMA1_Channel1->CMAR=(uint32_t)sbus_rx_buffer; 	//DMA1,�洢����ַ
	DMA1_Channel1->CNDTR=16;    	//DMA1,����������
	
	DMA1_Channel1->CCR|=0<<4;  		//�Ӵ洢����
	DMA1_Channel1->CCR|=1<<5;  		//��ͨģʽ
	DMA1_Channel1->CCR|=0<<6; 		//�����ַ������ģʽ
	DMA1_Channel1->CCR|=1<<7; 	 	//�洢������ģʽ
	DMA1_Channel1->CCR|=1<<8; 	 	//�������ݿ��Ϊ16λ
	DMA1_Channel1->CCR|=1<<10; 		//�洢�����ݿ��16λ
	DMA1_Channel1->CCR|=3<<12; 		//������ȼ�
	DMA1_Channel1->CCR|=0<<14; 		//�Ǵ洢�����洢��ģʽ	 
	DMA1_Channel1->CCR|=1<<1;
	DMA1_Channel1->CCR|=1<<0;
}

void  Adc_Init(void)
{    
	//�ȳ�ʼ��IO��
 	RCC->APB2ENR|=1<<2;    //ʹ��PORTA��ʱ�� 
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<4;
	GPIOA->CRL&=0X00000000;
	GPIOB->CRL&=0XFFFFFF00;
	GPIOC->CRL&=0XFF000000;
	RCC->APB2ENR|=1<<9;    //ADC1ʱ��ʹ��	  
	RCC->APB2RSTR|=1<<9;   //ADC1��λ
	RCC->APB2RSTR&=~(1<<9);//��λ����	    
	RCC->CFGR&=~(3<<14);   //��Ƶ��������	
	//SYSCLK/DIV2=12M ADCʱ������Ϊ12M,ADC���ʱ�Ӳ��ܳ���14M!
	//���򽫵���ADC׼ȷ���½�! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   //����ģʽ����
	ADC1->CR1|=0<<16;      //��������ģʽ   
	ADC1->CR1|=1<<8;    //ɨ��ģʽ	 
	ADC1->CR2|=1<<1;    //����ת��ģʽ
	ADC1->CR2&=~(1<<11);   //�Ҷ���	 
	ADC1->SQR1=0x00F4A1EE;
	ADC1->SQR2=0x0E62916C;	//��������1 ͨ��ch
	ADC1->SQR3=0x1A00886A;	//����ͨ��1�Ĳ���ʱ�� 
	ADC1->SMPR1&=0x00000000;
	ADC1->SMPR1|=0x00FFFFFF;
 	ADC1->SMPR2|=0x3FFFFFFF;     //239.5����	 
	ADC1->CR2|=1<<0;	   //����ADת����	 
	ADC1->CR2|=1<<3;       //ʹ�ܸ�λУ׼  
	while(ADC1->CR2&1<<3); //�ȴ�У׼���� 			 
    //��λ��������ò���Ӳ���������У׼�Ĵ�������ʼ�����λ��������� 		 
	ADC1->CR2|=1<<2;        //����ADУ׼	   
	while(ADC1->CR2&1<<2);  //�ȴ�У׼����
	//��λ����������Կ�ʼУ׼������У׼����ʱ��Ӳ����� 
 
}				  

void BSP_Configuration(void)
{
    NVIC_Configuration();
		Adc_Init();
		DMA_Config();
		ADC_DMACmd(ADC1, ENABLE);
		ADC1->CR2|=1<<0;       //����ת��
		Led_Configuration();
		ADC_Led_Configuration();
		KEY_Configuration();
//		USART3_Config();
		Can_chassis_one_motor_conf();
    TIM_Configuration();
}


	 










