#include "LED.h"

void LED_Cfg(void)
{
	GPIO_InitTypeDef led_gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	
	/* LED�Ƶ��������*/	
	led_gpio.GPIO_Pin=GPIO_Pin_5;
	led_gpio.GPIO_Mode=GPIO_Mode_Out_PP;//ͨ���������
	led_gpio.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&led_gpio);//PB5
	
	led_gpio.GPIO_Pin=GPIO_Pin_5;
	led_gpio.GPIO_Mode=GPIO_Mode_Out_PP;//ͨ���������
	led_gpio.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOE,&led_gpio);//PE5
	
	/*������ر����õ�LED��*/
	LED1_OFF;
	LED2_OFF;
}
