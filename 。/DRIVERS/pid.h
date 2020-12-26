#ifndef _PID_H
#define _PID_H

#include "user_code.h"

typedef struct
{
	float Target; 			        //设定目标值
	float err; 						//本次偏差值
	float err_last; 			    //上一次偏差
	float err_all; 			//偏差相加
	float pwm; 						//pwm输出

}Positional;//位置式pid

int Positional_pid(int Encoder,int Target);
#endif
