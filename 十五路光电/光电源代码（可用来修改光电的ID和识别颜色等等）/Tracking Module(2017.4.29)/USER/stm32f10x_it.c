#include "stm32f10x_it.h"
#include "stm32f10x_can.h" 
#include "FramWork.h"
#include "BSP.h"
#include "stmflash.h"

CAN_SEND_TYPE CAN_SEND_TYPEDEF;

extern adc_data_type adc_data_typedef;
extern u16 sbus_rx_buffer[16];
extern u16 adc_data[16];
u8 mode;
u16 count;
u8 cir;

u16 white_color_max[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
u16 other_color_min[16]={5000,5000,5000,5000,5000,5000,5000,5000,5000,5000,5000,5000,5000,5000,5000,5000};
u16 threshold_value[16];

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CanRxMsg  RxMessage;
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
}

void TIM7_IRQHandler(void)
{
	 
		MODE_CHANGE();
		if(mode==0)
		{
			DevelopmentFramwork();
			ADC_LED_SHOW();
			CAN_SetMsg(CAN_SEND_TYPEDEF.DATA_8,2,0X04);
		}
		else if(mode==21)//处于扫描浅色状态	
		{
			DevelopmentFramwork();	
			for(cir=0;cir<16;cir++)
			{
				if(white_color_max[cir]<adc_data[cir])
				{
					white_color_max[cir]=adc_data[cir];
				}
			}
		}
		else if(mode==22)//处于扫描深色状态	
		{
			DevelopmentFramwork();
			for(cir=0;cir<16;cir++)
			{
				if(other_color_min[cir]>adc_data[cir])
				{
					other_color_min[cir]=adc_data[cir];
				}
			}
		}	
		else if(mode==23)//保存退出
				 {	
					for(cir=0;cir<16;cir++)
						{
						 //保证本次操作深浅两色都有进行扫描过且不会深浅两色颠倒扫描		
						 if(white_color_max[cir]!=0&&other_color_min[cir]!=5000&&white_color_max[cir]<other_color_min[cir])			 
							{	
							  threshold_value[cir]=other_color_min[cir]*3/10+white_color_max[cir]*7/10;	//阀值计算公式
							}
						 else
							 mode=0;
						 white_color_max[cir]=0;
						 other_color_min[cir]=5000;	
			     	}	
					if(mode==23)
            {
							STMFLASH_Write(FLASH_SAVE_ADDR,threshold_value,16);	
							LED_ALL_OFF();
							for(cir=0;cir<20;cir++)
							{
								SysDelay_ms(50);
								LED4=!LED4;
								LED5=!LED5;
								LED6=!LED6;
								LED10=!LED10;
								LED11=!LED11;							
								LED12=!LED12;	
							 }
              mode=0;							
						}	
					LED_exit();
				 }
		TIM_ClearITPendingBit(TIM7,TIM_FLAG_Update);//中断标志位清除
}



void ADC_LED_SHOW(void)
{
	if(adc_data[1]<threshold_value[1])
	{
		LED1=1;
		CAN_SEND_TYPEDEF.DATA_16|=1;
	}
	else
	{
		LED1=0;
		CAN_SEND_TYPEDEF.DATA_16&=~1;
	}
	if(adc_data[2]<threshold_value[2])
	{
		LED2=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<1;
	}
	else
	{
		LED2=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<1);
	}
	if(adc_data[3]<threshold_value[3])
	{
		LED3=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<2;
	}
	else
	{
		LED3=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<2);
	}
	if(adc_data[4]<threshold_value[4])
	{
		LED4=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<3;
	}
	else
	{
		LED4=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<3);
	}
	if(adc_data[5]<threshold_value[5])
	{
		LED5=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<4;
	}
	else
	{
		LED5=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<4);
	}
	if(adc_data[6]<threshold_value[6])
	{
		LED6=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<5;
	}
	else
	{
		LED6=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<5);
	}
	if(adc_data[7]<threshold_value[7])
	{
		LED7=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<6;
	}
	else
	{
		LED7=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<6);
	}
	if(adc_data[8]<threshold_value[8])
	{
		LED8=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<7;
	}
	else
	{
		LED8=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<7);
	}
	if(adc_data[9]<threshold_value[9])
	{
		LED9=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<8;
	}
	else
	{
		LED9=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<8);
	}
	if(adc_data[10]<threshold_value[10])
	{
		LED10=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<9;
	}
	else
	{
		LED10=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<9);
	}
	if(adc_data[11]<threshold_value[11])
	{
		LED11=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<10;
	}
	else
	{
		LED11=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<10);
	}
	if(adc_data[12]<threshold_value[12])
	{
		LED12=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<11;
	}
	else
	{
		LED12=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<11);
	}
	if(adc_data[13]<threshold_value[13])
	{
		LED13=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<12;
	}
	else
	{
		LED13=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<12);
	}
	if(adc_data[14]<threshold_value[14])
	{
		LED14=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<13;
	}
	else
	{
		LED14=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<13);
	}
	if(adc_data[15]<threshold_value[15])
	{
		LED15=1;
		CAN_SEND_TYPEDEF.DATA_16|=1<<14;
	}
	else
	{
		LED15=0;
		CAN_SEND_TYPEDEF.DATA_16&=~(1<<14);
	}
}

void MODE_CHANGE(void)
{
	if(KEY==0)//按下按键
		{
			LED0=1;
		  count++;
			if(count==150)//长按
				{
					LED0=0;
					if(mode==0)
						{
							mode=1;
							LED_enter();
							LED_mode1();
						}
					else if(mode==1)
						{
							mode=21;
							LED_ALL_OFF();
						}
					else if(mode==2)	
						{
							mode=22;
							LED_ALL_OFF();
						}	
					else if(mode==3)
						{
							mode=23;						
						}							
				}				
		}
	else if(KEY==1)//松开按键
		{
			if(mode!=0)
				LED0=0;
			if(count>3 && count<150)//短按
				{
					if(mode==1)
						mode=2;
					else if(mode==2)
						mode=3;
					else if(mode==3||mode==21||mode==22)
						mode=1;						
		    }
			if(mode==1)
				LED_mode1();								
			else if(mode==2)
				LED_mode2();					
			else if(mode==3)
				LED_mode3();					
      count=0;				
		}
}

void LED_ALL_ON(void)
{
	LED1=1;
	LED2=1;
	LED3=1;
	LED4=1;
	LED5=1;
	LED6=1;
	LED7=1;
	LED8=1;
	LED9=1;
	LED10=1;
	LED11=1;
	LED12=1;
	LED13=1;
	LED14=1;
	LED15=1;
}

void LED_ALL_OFF(void)
{
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=0;
	LED6=0;
	LED7=0;
	LED8=0;
	LED9=0;
	LED10=0;
	LED11=0;
	LED12=0;
	LED13=0;
	LED14=0;
	LED15=0;
}

void LED_enter(void)
{
	LED_ALL_OFF();
	SysDelay_ms(500);
	LED8=1;
	SysDelay_ms(50);
	LED7=1;
	LED9=1;
	SysDelay_ms(50);
	LED6=1;
	LED10=1;
	SysDelay_ms(50);
	LED5=1;
	LED11=1;
	SysDelay_ms(50);
	LED4=1;
	LED12=1;
	SysDelay_ms(50);
	LED3=1;
	LED13=1;
	SysDelay_ms(50);
	LED2=1;
	LED14=1;
	SysDelay_ms(50);
	LED1=1;
	LED15=1;
	SysDelay_ms(500);
}

void LED_exit(void)
{
	LED_ALL_ON();
	SysDelay_ms(500);
  LED1=0;
	LED15=0;
	SysDelay_ms(50);
	LED2=0;
	LED14=0;
	SysDelay_ms(50);
	LED3=0;
	LED13=0;
	SysDelay_ms(50);
	LED4=0;
	LED12=0;
	SysDelay_ms(50);
	LED5=0;
	LED11=0;
	SysDelay_ms(50);
	LED5=0;
	LED11=0;
	SysDelay_ms(50);
	LED6=0;
	LED10=0;
	SysDelay_ms(50);
	LED7=0;
	LED9=0;
	SysDelay_ms(50);
	LED8=0;
}

void LED_mode1(void)
{
	LED1=0;
	LED2=0;
	LED3=0;
	LED4=0;
	LED5=0;
	LED6=0;
	LED7=1;
	LED8=1;
	LED9=1; 
	LED10=0;
	LED11=0;
	LED12=0;
	LED13=0;
	LED14=0;
	LED15=0;
}

void LED_mode2(void)
{
	LED1=1;
	LED2=1;
	LED3=1;
	LED4=0;
	LED5=0;
	LED6=0;
	LED7=0;
	LED8=0;
	LED9=0;
	LED10=0;
	LED11=0;
	LED12=0;
	LED13=1;
	LED14=1;
	LED15=1;
}

void LED_mode3(void)
{
	LED1=1;
	LED2=1;
	LED3=1;
	LED4=0;
	LED5=0;
	LED6=0;
	LED7=1;
	LED8=1;
	LED9=1;
	LED10=0;
	LED11=0;
	LED12=0;
	LED13=1;
	LED14=1;
	LED15=1;
}

void DMA1_Channel1_IRQHandler(void)
{	
	static u8 count;
	if(DMA_GetFlagStatus(DMA1_FLAG_TC1)==SET) 
		{  
			DMA_ClearFlag(DMA1_FLAG_TC1); 
			DMA_ClearITPendingBit(DMA1_IT_TC1);
			adc_data_typedef.data1[count]=sbus_rx_buffer[0];
			adc_data_typedef.data2[count]=sbus_rx_buffer[1];
			adc_data_typedef.data3[count]=sbus_rx_buffer[2];
			adc_data_typedef.data4[count]=sbus_rx_buffer[3];
			adc_data_typedef.data5[count]=sbus_rx_buffer[4];
			adc_data_typedef.data6[count]=sbus_rx_buffer[5];
			adc_data_typedef.data7[count]=sbus_rx_buffer[6];
			adc_data_typedef.data8[count]=sbus_rx_buffer[7];
			adc_data_typedef.data9[count]=sbus_rx_buffer[8];
			adc_data_typedef.data10[count]=sbus_rx_buffer[9];
			adc_data_typedef.data11[count]=sbus_rx_buffer[10];
			adc_data_typedef.data12[count]=sbus_rx_buffer[11];
			adc_data_typedef.data13[count]=sbus_rx_buffer[12];
			adc_data_typedef.data14[count]=sbus_rx_buffer[13];
			adc_data_typedef.data15[count]=sbus_rx_buffer[14];
			adc_data_typedef.data16[count]=sbus_rx_buffer[15];
			count++;
			if(count==9)
			{
				count=0;
			}
		}
}
