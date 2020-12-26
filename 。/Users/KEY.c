#include "KEY.h"

void KEY_Cfg(void)
{
	GPIO_InitTypeDef key_gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE);
	/*∞¥º¸≈‰÷√*/
  key_gpio.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4;
	key_gpio.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOE,&key_gpio);
	
	key_gpio.GPIO_Pin=GPIO_Pin_0;
	key_gpio.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Init(GPIOA,&key_gpio);
	
}

