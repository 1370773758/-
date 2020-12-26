#ifndef __BSP_H
#define __BSP_H	

#include "stm32f10x.h"
#include "BitBand.h"
#include "stm32f10x_can.h"
#define PWMPeriod      7200			//10k HZ
#define ECDPeriod      20000
#define TIMPeriod	     5000
#define PWMLOSS        500	



#define LED0  PBout(7)	
#define LED1  PAout(15)
#define LED2  PCout(10)
#define LED3  PCout(11)
#define LED4  PCout(12)
#define LED5  PDout(2)
#define LED6  PBout(3)
#define LED7  PBout(4)
#define LED8  PCout(9)
#define LED9  PCout(8)
#define LED10 PCout(7)
#define LED11 PCout(6)
#define LED12 PBout(15)
#define LED13 PBout(14)
#define LED14 PBout(13)
#define LED15 PBout(12)

#define KEY PAin(8)


#define Sys_us  72/8            
#define Sys_ms  Sys_us*1000

#define prd     ECDPeriod
#define Vbreak  ECDPeriod/2

/* ----------------------- RC Channel Definition---------------------------- */ 
#define RC_CH_VALUE_MIN              ((uint16_t)364 ) 
#define RC_CH_VALUE_OFFSET           ((uint16_t)1024) 
#define RC_CH_VALUE_MAX              ((uint16_t)1684) 
 
/* ----------------------- RC Switch Definition----------------------------- */ 
#define RC_SW_UP                     ((uint16_t)1) 
#define RC_SW_MID                    ((uint16_t)3) 
#define RC_SW_DOWN                   ((uint16_t)2) 
 
/* ----------------------- PC Key Definition-------------------------------- */ 
#define KEY_PRESSED_OFFSET_W         ((uint16_t)0x01<<0) 
#define KEY_PRESSED_OFFSET_S         ((uint16_t)0x01<<1) 
#define KEY_PRESSED_OFFSET_A         ((uint16_t)0x01<<2) 
#define KEY_PRESSED_OFFSET_D         ((uint16_t)0x01<<3) 
#define KEY_PRESSED_OFFSET_Q         ((uint16_t)0x01<<4) 
#define KEY_PRESSED_OFFSET_E         ((uint16_t)0x01<<5) 
#define KEY_PRESSED_OFFSET_SHIFT     ((uint16_t)0x01<<6) 
#define KEY_PRESSED_OFFSET_CTRL      ((uint16_t)0x01<<7) 
 
/* ----------------------- Data Struct ------------------------------------- */ 




typedef union
{
	char speed_data_8[8];
	s16 speed_data_16[4];
}speed_data_type;

 
void NVIC_Configuration(void);
void TIM7_Configuration(void);
void TIM_Configuration(void);
void Led_Configuration(void);
void ADC_Led_Configuration(void);
void KEY_Configuration(void);
void BSP_Configuration(void);
void Systick_Configuration(void);
void SysDelay_ms(u16 nms);
void SysDelay_us(u32 nus);
void USART3_Config(void);
void DMA_Config(void);
void Adc_Init(void);

static void Can_chassis_one_motor_gpio_conf(void);
static void Can_chassis_one_motor_nvic_conf(void);
static void Can_chassis_one_motor_init_conf(void);
static void Can_chassis_one_motor_filter_conf(void);
void Can_chassis_one_motor_conf(void);
void CAN_SetMsg(char* data,char num,int CAN_ID);

#endif















