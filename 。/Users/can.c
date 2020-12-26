#include "can.h"
/* can ͨѶʵ�� */
u8 flag=0;



void can_cfg(void)
{
	GPIO_InitTypeDef      gpio_init;
	CAN_InitTypeDef       can_init;
	CAN_FilterInitTypeDef can_filterinit;
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE );
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_CAN1 ,ENABLE);
	
	gpio_init.GPIO_Pin=GPIO_Pin_11;
	gpio_init.GPIO_Mode=GPIO_Mode_AF_PP ;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init);
	
	gpio_init.GPIO_Pin=GPIO_Pin_12;
	gpio_init.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA ,&gpio_init);
	
	//can��Ԫ���� ���ù���ģʽ
	can_init.CAN_Mode=CAN_Mode_Normal;//�ػ�ģʽ����������Ϊ��ͨģʽ
	can_init.CAN_TTCM=DISABLE;			//��ʱ�䴥��ͨ��ģʽ  
	can_init.CAN_ABOM=ENABLE;			//����Զ����߹���	 
	can_init.CAN_AWUM=ENABLE;			//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
	can_init.CAN_NART=ENABLE;			//���Ĵ����Զ����� 
	can_init.CAN_RFLM=ENABLE;		 	//���Ĳ�����,�µĸ��Ǿɵ�  
	can_init.CAN_TXFP=DISABLE;			//���ȼ��ɱ��ı�ʶ������ 
	//���ò����� 1Mbps SYNC_SE�ι̶���1Tq
	can_init.CAN_SJW=CAN_SJW_1tq;
	can_init.CAN_BS1=CAN_BS1_5tq;
	can_init.CAN_BS2=CAN_BS2_3tq;//bs1+bs2+se��=9Tq
	can_init.CAN_Prescaler=4;//�ڲ����Լ�1
	CAN_Init(CAN1 ,&can_init);
/* can������ */
	can_filterinit.CAN_FilterActivation=ENABLE; //�Ƿ�ʹ�ܹ�����
	can_filterinit.CAN_FilterFIFOAssignment=CAN_FilterFIFO0;//���ݴ���FIFO0
	can_filterinit.CAN_FilterNumber=0;//0��13
	can_filterinit.CAN_FilterScale=CAN_FilterScale_32bit;//16λ 32λ
	can_filterinit.CAN_FilterMode=CAN_FilterMode_IdMask;
	/* ���˵�����չ֡����չ����֡ */
	can_filterinit.CAN_FilterIdHigh=0x0000;//((PASS_ID<<3|CAN_ID_EXT|CAN_RTR_Data)&0xFFFF0000)>>16;//���˵�ID
	can_filterinit.CAN_FilterIdLow=0x0000;//((PASS_ID<<3|CAN_ID_EXT|CAN_RTR_Data)&0xFFFF);
	/*��չ����֡�ĵ�16λ������Ҫλ�� */
	can_filterinit.CAN_FilterMaskIdHigh=0x01E0;//0xFFFF;//32λMASK
	can_filterinit.CAN_FilterMaskIdLow=0x0000;//0xFFFF;//������������
	CAN_FilterInit(&can_filterinit);			//�˲�����ʼ��

	nvic_cfg (USB_LP_CAN1_RX0_IRQn,1,1);//��������0
	/*�жϺ�����Ļ� �Ῠ�������ļ�*/
	CAN_ITConfig (CAN1 ,CAN_IT_FMP0,ENABLE );//CAN_IT_FMP0��������0�������ж�,ʹ���ж�
	
	CAN_Receive(CAN1,CAN_FIFO0,&CAN_Rece_Data);
}
