#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H
#include "stm32f10x.h"

typedef struct
{
  char data_num;
  char data_count;

} serialreadtype;

typedef union
{
  u16 DATA_16;
  char DATA_8[2];
} CAN_SEND_TYPE;

void TIM6_IRQHandler(void);
void TIM7_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void ADC_LED_SHOW(void);
void MODE_CHANGE(void);
void LED_ALL_OFF(void);
void LED_ALL_ON(void);
void LED_enter(void);
void LED_exit(void);
void LED_mode1(void);
void LED_mode2(void);
void LED_mode3(void);

#endif


















