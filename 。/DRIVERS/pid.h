#ifndef _PID_H
#define _PID_H

#include "user_code.h"

typedef struct
{
	float Target; 			        //�趨Ŀ��ֵ
	float err; 						//����ƫ��ֵ
	float err_last; 			    //��һ��ƫ��
	float err_all; 			//ƫ�����
	float pwm; 						//pwm���

}Positional;//λ��ʽpid

int Positional_pid(int Encoder,int Target);
#endif
