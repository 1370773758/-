#include "pid.h"

float kp=13.5;//13.5//11.5
float ki=0.241;//0.24
float kd=14.5;//14.5
float err_all;

int Positional_pid(int Encoder,int Target)
{
	Positional pid;
	
	pid.err = Encoder - Target;
	err_all += pid.err;

	pid.pwm = kp*pid.err + ki*err_all + kd*(pid.err - pid.err_last);
	
//	if(pid.err<200) pid.err_last=0;

	if (pid.pwm>7200)
		pid.pwm = 7200;
	else if (pid.pwm<-7200)
		pid.pwm = -7200;

	pid.err_last = pid.err;
	return pid.pwm;
}

