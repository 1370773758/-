#include "tim.h"
/* ��ʱ���ж�ʹled��5s��˸*/
void tim6_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef tim_init;
	
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM6,ENABLE );
	
	tim_init .TIM_Period =arr;
	tim_init .TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM6 ,&tim_init);
	
	TIM_ClearFlag (TIM6,TIM_FLAG_Update);
	TIM_ITConfig (TIM6,TIM_IT_Update,ENABLE );
	nvic_cfg (TIM6_IRQn,2,0);
	TIM_Cmd (TIM6,ENABLE );
}

void tim7_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
	/* ����ʱ���ṹ�� */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	//ʹ�ܶ�ʱ��ʱ��
  
	TIM_TimeBaseStructure.TIM_Prescaler = psc;   
	//���ö�ʱ��ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_Period = arr;         
	//�����Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	//��ʼ��TIM6ʱ�������λ

	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	//��������жϣ���ֹһ���ж���������ж�
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	//�򿪶�ʱ�������ж�

	nvic_cfg(TIM7_IRQn, 1, 0);
	/*�����ж����ȼ�*/
	TIM_Cmd(TIM7, ENABLE);
	//ʹ�ܶ�ʱ��
}
