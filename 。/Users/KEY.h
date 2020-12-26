#ifndef _KEY_H
#define _KEY_H

#include "user_code.h"

//#define KEY_DN  1    //按键按下
//#define KEY_OFF 0		//按键松开

#define KEY3_STA GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY2_STA GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define KEY1_STA GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)

void KEY_Cfg(void);
#endif
