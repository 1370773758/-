#include "user_code.h"

void Init(void)
{
	LED_Cfg();
	KEY_Cfg();
//	exti_cfg();

usart_cfg();
//	usart1_cfg();
	servo();
	
//	tim6_init(49999,7199);
//	tim7_init(49,7199);
	
can_cfg();
//	encoder(0, 65535);
//	Motor_Tim_Config();
}
