#ifndef _LED_H
#define _LED_H

#include "user_code.h"
/*寄存器宏定义*/
#define LED1_TOGGLE 	 	 GPIOB->ODR^=GPIO_Pin_5//红灯
#define LED1_ON    			 GPIOB->BRR=GPIO_Pin_5
#define LED1_OFF   			 GPIOB->BSRR=GPIO_Pin_5
/*库函数定义*/
#define LED2_ON			     	GPIO_ResetBits(GPIOE,GPIO_Pin_5)
#define LED2_OFF					GPIO_SetBits(GPIOE,GPIO_Pin_5)//绿灯
void LED_Cfg(void);
#endif
