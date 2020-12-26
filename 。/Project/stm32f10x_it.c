/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 

 #if 1
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}
#endif
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

#if 1
//void EXTI4_IRQHandler(void)
//{
//	delay_ms (10);
//	if(KEY1_STA ==0)
//	{
//		LED1_ON ;
//	}
//	if(KEY1_STA ==1)
//	{
//		LED1_OFF ;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line4);
//}
//void EXTI3_IRQHandler(void)
//{
//	delay_ms (10);
//	if(KEY2_STA ==0)
//	{
//		LED2_ON;
//	}
//	if(KEY2_STA ==1)
//	{
//		LED2_OFF ;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line3);
//}
//void EXTI0_IRQHandler(void)
//{
//	delay_ms (10);
//	if(KEY3_STA==1)
//		{
//			LED1_ON;
//			LED2_ON;
//		}
//	if(KEY3_STA ==0)
//	{
//		LED1_OFF ;
//		LED2_OFF ;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line0);
//}
#endif
int res,pwm;
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{	
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//清除中断标志位
			USART_SendData(USART2,res);
			res=USART_ReceiveData(USART2);
//		if(res=='1')
//		{
//			LED1_ON;
//     printf("\r\n -------红灯亮！------ \r\n");
//		}
//			if(res=='2')
//		{
//			LED1_OFF;
//     printf("\r\n -------红灯灭！------ \r\n");
//		}
//		if(res=='3')
//		{
//			LED2_ON;
//     printf("\r\n -------绿灯亮！------ \r\n");
//		}
//			if(res=='4')
//		{
//			LED2_OFF;
//     printf("\r\n -------绿灯灭！------ \r\n");
//		}
//	}
//	  if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) == SET) //在卡住的地方加入这个就能解决
////  {
//    USART_ClearFlag(USART2,USART_FLAG_ORE);
//    USART_ReceiveData(USART2);
  }
}

int i;
//void TIM6_IRQHandler(void)
//{
//  if (TIM_GetITStatus (TIM6,TIM_IT_Update)!=RESET)//(TIM6->SR & 0X0001)	
//		{
//		i++;
//		LED1_ON;
//		if(i%2==0)
//		{
//			LED2_ON;
//			delay_ms(100);
//			LED2_OFF ;
//		}
//		else delay_ms (100);
//		LED1_OFF ;
//		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
//	}
//}
int j;
void TIM7_IRQHandler(void)
{
	j++;
	if (TIM7->SR & 0X0001)
	{
		Encoder =Read_Encoder(4);
		motor=Positional_pid(Encoder,Target );
		pwm_cfg(motor);
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	}
}


//PS_TYPE PS_SEF;
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0 )!=RESET)
	{
//		CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
//		CAN_Receive(CAN1,CAN_FIFO0 ,&CAN_Rece_Data);
//		if((CAN_Rece_Data.StdId==0x01)&&(CAN_Rece_Data.IDE==CAN_ID_STD))
//		{
//			
//		}
	}
	CAN_Receive (CAN1 ,CAN_FIFO0,&CAN_Rece_Data);//接受的数据位存储在这里
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
