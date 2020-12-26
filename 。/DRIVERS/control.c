#include "control.h"
/* 舵机角度控制*/

int Target=0;
int Encoder,motor;

void sg90(int angle)
{
	int pwm;
//	if(pwm>180) angle=180;
//	if(angle<0) angle=0;
	
	pwm=10*angle/9+50;
	TIM3->CCR1 =pwm;
}

/*电机输出*/
void pwm_cfg(int motor)
{
	if (motor > 0)
	{
	TIM8 ->CCR2 = 7200;
	TIM8->CCR1= 7200 - motor;
	}
	if(motor<0) 	              
	{
		TIM8->CCR1  = 7200;
	TIM8 ->CCR2= 7200 + motor;
	}
}


