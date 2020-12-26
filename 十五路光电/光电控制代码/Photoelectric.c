/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|--FileName    : Photoelectric.c                                              
|--Version     : v1.0                                                          
|--Author      : Daqo Lee                                                     
|--Date        : 2019-03-18             
|--Libsupports : STM32F4xx_DFP ( 2.9.0)
|--Description :                                                     
|-----------------------------declaration of end-------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Photoelectric.h"
#include "Chassis.h"
  
/*-------------------------- D E F I N E S -----------------------------------*/
#define k 2				//k值可调整
float PS_CV[15]={-7*k,-6*k,-5*k,-4*k,-3*k,-2*k,-1*k,0,1*k,2*k,3*k,4*k,5*k,6*k,7*k};		//作为15路光电每一路的权值
	
	

	
PS_TYPE PS_DEF;
PS_C_TYPE PS_C_DEF;  
PID_AbsoluteType PSX_PID_DEF,PSY_PID_DEF,PSZ_PID_DEF;
extern Chassis_t Chassis;
/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



/*------------------G L O B A L - F U N C T I O N S --------------------------*/

	
	/***************绝对式PID****************/
void PID_AbsoluteMode(PID_AbsoluteType* PID)
{

	 if(PID->kp      < 0)    PID->kp      = -PID->kp;
	 if(PID->ki      < 0)    PID->ki      = -PID->ki;
	 if(PID->kd      < 0)    PID->kd      = -PID->kd;
	 if(PID->errILim < 0)    PID->errILim = -PID->errILim;

	 PID->errP = PID->errNow;  //读取现在的误差，用于kp控制

	 PID->errI += PID->errNow; //误差积分，用于ki控制

	 if(PID->errILim != 0)	   //微分上限和下限
	 {
		if(     PID->errI >  PID->errILim)    PID->errI =  PID->errILim;
		else if(PID->errI < -PID->errILim)    PID->errI = -PID->errILim;
	 }
	 
	 PID->errD = PID->errNow - PID->errOld;//误差微分，用于kd控制

	 PID->errOld = PID->errNow;	//保存现在的误差
	 
	 PID->ctrOut = PID->kp * PID->errP + PID->ki * PID->errI + PID->kd * PID->errD;//计算绝对式PID输出

}
	

//光电位置矫正，用于十字白线矫正位置

	void PS_Checkout(void)															
{
	float KP=30,KI=0,KD=10; //40
	s16 temp_y,temp_x,temp_spin;
	PS_control_clear(&PS_C_DEF);
		PS_DATA_analyze(PS_DEF.Front.DATA_16,&PS_C_DEF.UP_control,&PS_C_DEF.UP_PSnum,&PS_C_DEF.UP_last);
		PS_DATA_analyze(PS_DEF.Back.DATA_16,&PS_C_DEF.DOWN_control,&PS_C_DEF.DOWN_PSnum,&PS_C_DEF.DOWN_last);
		PS_DATA_analyze(PS_DEF.Left.DATA_16,&PS_C_DEF.LEFT_control,&PS_C_DEF.LEFT_PSnum,&PS_C_DEF.LEFT_last);
		PS_DATA_analyze(PS_DEF.Right.DATA_16,&PS_C_DEF.RIGHT_control,&PS_C_DEF.RIGHT_PSnum,&PS_C_DEF.RIGHT_last);
		{
			PSY_PID_DEF.errNow=PS_C_DEF.RIGHT_control;
			PSY_PID_DEF.kp=KP;
			PSY_PID_DEF.ki=0;
			PSY_PID_DEF.kd=KD;
			PSY_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSY_PID_DEF);
			
			temp_y=PSY_PID_DEF.ctrOut;
			
			PSY_PID_DEF.errNow=PS_C_DEF.LEFT_control;
			PSY_PID_DEF.kp=KP;
			PSY_PID_DEF.ki=0;
			PSY_PID_DEF.kd=KD;
			PSY_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSY_PID_DEF);
			
			Chassis.Vy=(PSY_PID_DEF.ctrOut+temp_y);
		}
		{
			PSX_PID_DEF.errNow=PS_C_DEF.DOWN_control;
			PSX_PID_DEF.kp=KP;
			PSX_PID_DEF.ki=0;
			PSX_PID_DEF.kd=KD;
			PSX_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSX_PID_DEF);
			
			temp_x=PSX_PID_DEF.ctrOut;
			
			PSX_PID_DEF.errNow=PS_C_DEF.UP_control;
			PSX_PID_DEF.kp=KP;
			PSX_PID_DEF.ki=0;
			PSX_PID_DEF.kd=KD;
			PSX_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSX_PID_DEF);
			Chassis.Vx=(PSX_PID_DEF.ctrOut+temp_x);
		}
		{
			PSZ_PID_DEF.errNow=PS_C_DEF.DOWN_control-PS_C_DEF.UP_control;
			PSZ_PID_DEF.kp=10;  //50   20
			PSZ_PID_DEF.ki=0;
			PSZ_PID_DEF.kd=10;
			PSZ_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSZ_PID_DEF);
			
			temp_spin=PSZ_PID_DEF.ctrOut;
			
			PSZ_PID_DEF.errNow=PS_C_DEF.RIGHT_control-PS_C_DEF.LEFT_control;
			PSZ_PID_DEF.kp=10;		//50   20
			PSZ_PID_DEF.ki=0;
			PSZ_PID_DEF.kd=10;
			PSZ_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSZ_PID_DEF);
			
			Chassis.Vspin=(PSZ_PID_DEF.ctrOut+temp_spin);
		}
	
}



//用于一个方向（即一条白线）的位置矫正

	void Posture_X_Checkout(void)
	{
		static	float KP=20,KI=0,KD=2; //40
		int16_t temp_x;
		PS_control_clear(&PS_C_DEF);
		PS_DATA_analyze(PS_DEF.Front.DATA_16,&PS_C_DEF.UP_control,&PS_C_DEF.UP_PSnum,&PS_C_DEF.UP_last);
		PS_DATA_analyze(PS_DEF.Back.DATA_16,&PS_C_DEF.DOWN_control,&PS_C_DEF.DOWN_PSnum,&PS_C_DEF.DOWN_last);
		{
			PSX_PID_DEF.errNow=PS_C_DEF.DOWN_control;
			PSX_PID_DEF.kp=KP;
			PSX_PID_DEF.ki=0;
			PSX_PID_DEF.kd=KD;
			PSX_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSX_PID_DEF);
			temp_x=PSX_PID_DEF.ctrOut;
			
			PSX_PID_DEF.errNow=PS_C_DEF.UP_control;
			PSX_PID_DEF.kp=KP;
			PSX_PID_DEF.ki=0;
			PSX_PID_DEF.kd=KD;
			PSX_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSX_PID_DEF);
			Chassis.Vx = (PSX_PID_DEF.ctrOut+temp_x);
		}
		
	}
	
	
	//用于一个方向（即一条白线）的位置矫正
	void Posture_x_Checkout(void)
	{
		static	float KP=20,KI=0,KD=2; //40
		int16_t temp_x;
		PS_control_clear(&PS_C_DEF);
		PS_DATA_analyze(PS_DEF.Left.DATA_16,&PS_C_DEF.LEFT_control,&PS_C_DEF.LEFT_PSnum,&PS_C_DEF.LEFT_last);
		PS_DATA_analyze(PS_DEF.Right.DATA_16,&PS_C_DEF.RIGHT_control,&PS_C_DEF.RIGHT_PSnum,&PS_C_DEF.RIGHT_last);
		
		{
			PSX_PID_DEF.errNow=PS_C_DEF.LEFT_control;
			PSX_PID_DEF.kp=KP;
			PSX_PID_DEF.ki=0;
			PSX_PID_DEF.kd=KD;
			PSX_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSX_PID_DEF);
			
			temp_x=PSX_PID_DEF.ctrOut;
			
			PSX_PID_DEF.errNow=PS_C_DEF.RIGHT_control;
			PSX_PID_DEF.kp=KP;
			PSX_PID_DEF.ki=0;
			PSX_PID_DEF.kd=KD;
			PSX_PID_DEF.errILim=1500;
			PID_AbsoluteMode(&PSX_PID_DEF);
			Chassis.Vy = (PSX_PID_DEF.ctrOut+temp_x);
		}
		
		
	}


//光电数据解析
	
void PS_DATA_analyze(u16 PS_data,float *control_data,u8 *PS_num,float *control_last)	
{
	u8 cir;
		for(cir=1;cir<16;cir++)
		{
			if(((PS_data>>(cir-1))&0x1)==1)
			{
				*control_data+=PS_CV[cir-1];
				(*PS_num)++;
			}
		}		
		if(*PS_num==0)
		{
			*control_data=*control_last;
		}
		else
		{
			*control_data=*control_data/(*PS_num);
		}
}



//光电数据初始化清零

void PS_control_clear(PS_C_TYPE *data)
{
	data->DOWN_last=0;
	data->DOWN_control=0;
	data->DOWN_PSnum=0;
	
	
	data->UP_last=0;
	data->UP_control=0;
	data->UP_PSnum=0;
	
	
	data->LEFT_last=0;
	data->LEFT_control=0;
	data->LEFT_PSnum=0;
	
	
	data->RIGHT_last=0;
	data->RIGHT_control=0;
	data->RIGHT_PSnum=0;
	
}

	
	
/*---------------------L O C A L - F U N C T I O N S--------------------------*/



/*-----------------------------------file of end------------------------------*/


