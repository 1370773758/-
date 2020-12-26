#include "LED.h"

void LED_Cfg(void)
{
	GPIO_InitTypeDef led_gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	
	/* LED灯的相关配置*/	
	led_gpio.GPIO_Pin=GPIO_Pin_5;
	led_gpio.GPIO_Mode=GPIO_Mode_Out_PP;//通用推挽输出
	led_gpio.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&led_gpio);//PB5
	
	led_gpio.GPIO_Pin=GPIO_Pin_5;
	led_gpio.GPIO_Mode=GPIO_Mode_Out_PP;//通用推挽输出
	led_gpio.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOE,&led_gpio);//PE5
	
	/*配置完关闭所用的LED灯*/
	LED1_OFF;
	LED2_OFF;
}
