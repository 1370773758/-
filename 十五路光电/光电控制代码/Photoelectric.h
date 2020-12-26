/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|--FileName    : Photoelectric.h                                                
|--Version     : v1.0                                                            
|--Author      : Daqo Lee                                                         
|--Date        : 2019-03-18               
|--Libsupports : 
|--Description : STM32F4xx_DFP ( 2.9.0)                                                      
|-----------------------------declaration of end-------------------------------|
 **/
#ifndef __PHOTOELECTRIC_H 
#define __PHOTOELECTRIC_H 


/*--------------------- I N C L U D E - F I L E S ----------------------------*/

#include "stm32f4xx.h"

/*-------------------------G L O B A L - T Y P E S----------------------------*/

typedef struct
{
	union
	{
		u8 DATA_8[2];
		u16 DATA_16;
	}Front;
	
	union
	{
		u8 DATA_8[2];
		u16 DATA_16;
	}Back;
	
	union
	{
		u8 DATA_8[2];
		u16 DATA_16;
	}Left;
	
	union
	{
		u8 DATA_8[2];
		u16 DATA_16;
	}Right;
	
}PS_TYPE;													//��紫��������




typedef struct
{
		float UP_control;
		float UP_last;
		u8 UP_PSnum;
	
		float DOWN_control;
		float DOWN_last;
		u8 DOWN_PSnum;
	
		float LEFT_control;
		float LEFT_last;
		u8 LEFT_PSnum;
	
		float RIGHT_control;
		float RIGHT_last;
		u8 RIGHT_PSnum;
	
		u8 PS_C_Statu;
}PS_C_TYPE;

typedef struct        
{
 /*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
 float kp;     //����ϵ��
 float ki;     //����ϵ��
 float kd;     //΢��ϵ��
 float errILim;//����������
 
 float errNow;//��ǰ�����
 float ctrOut;//���������
 
 /*PID�㷨�ڲ���������ֵ�����޸�*/
 float errOld;
 float errP;
 float errI;
 float errD;
 
}PID_AbsoluteType;







/*------------------------G L O B A L - M A C R O S --------------------------*/



/*----------------------G L O B A L - D E F I N E S---------------------------*/



/*-----------G L O B A L - F U N C T I O N S - P R O T O T Y P E S------------*/

void PID_AbsoluteMode(PID_AbsoluteType* PID);
void PS_control_clear(PS_C_TYPE *data);
void PS_Checkout(void);
void Posture_X_Checkout(void);
void Posture_x_Checkout(void);

void PS_DATA_analyze(u16 PS_data,float *control_data,u8 *PS_num,float *control_last);	//������ݽ���



#endif	// __PHOTOELECTRIC_H
/*-----------------------------------file of end------------------------------*/


