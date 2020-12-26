#ifndef _CONTROL_H
#define _CONTROL_H

#include "user_code.h"

#define PWMA      TIM2->CCR1  
#define PWMB      TIM2->CCR2 

extern int Target,Encoder,motor;

void sg90(int angle);
void pwm_cfg(int motor);

#endif
