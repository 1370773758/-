#include "user_code.h"
u8 box;
CanRxMsg  CAN_Rece_Data;//���ܵ����ݴ洢������
CanTxMsg	CAN_Tran_Data;//���͵�����

void Delay(uint32_t nCount);
int m;
int main(void)
{
	Init();
	LED2_ON;
	printf("/r/n����һ��CANͨѶʵ��/r/n");
	while(1)
	{
//		if(KEY1_STA==0)
//		{
//			CAN_Tran_Data.StdId=0;
//			CAN_Tran_Data.ExtId=PASS_ID;//���͵�����չ֡
//			CAN_Tran_Data.RTR=CAN_RTR_Data;//����֡
//			CAN_Tran_Data.IDE=CAN_Id_Extended;
//			CAN_Tran_Data.DLC=1;//һ���ֽ�
//			CAN_Tran_Data.Data[0]=10;
//			/*CAN_Transmit()���ص������ķ�������� */
//			box=CAN_Transmit (CAN1 ,&CAN_Tran_Data);
//			while(CAN_TransmitStatus(CAN1 ,box)==CAN_TxStatus_Failed);
//			/* �ȴ����ĵķ������*/
//			printf ("/r/n�����������/r/n");
//		}
//		if(flag==1)
//		{
//			printf("/r/n���ܵ������ǣ�%d/r/n",CAN_Rece_Data.Data[0]);
//			flag =0;
//		}
	}
	#if 0
	while(1)
	{
	sg90(m);//��ֵ0��180

//  Debug_addData((float)Target, 1);
//	Debug_addData( (float)Encoder, 2 );
//	Debug_show(2);
	delay_ms(100);
//		
	}
	#endif
}

void Delay(uint32_t nCount)
{
	for(;nCount !=0;nCount--);
}
