#include "user_code.h"
u8 box;
CanRxMsg  CAN_Rece_Data;//接受的数据存储在这里
CanTxMsg	CAN_Tran_Data;//发送的数据

void Delay(uint32_t nCount);
int m;
int main(void)
{
	Init();
	LED2_ON;
	printf("/r/n这是一个CAN通讯实验/r/n");
	while(1)
	{
//		if(KEY1_STA==0)
//		{
//			CAN_Tran_Data.StdId=0;
//			CAN_Tran_Data.ExtId=PASS_ID;//发送的是扩展帧
//			CAN_Tran_Data.RTR=CAN_RTR_Data;//数据帧
//			CAN_Tran_Data.IDE=CAN_Id_Extended;
//			CAN_Tran_Data.DLC=1;//一个字节
//			CAN_Tran_Data.Data[0]=10;
//			/*CAN_Transmit()返回的是他的发送邮箱号 */
//			box=CAN_Transmit (CAN1 ,&CAN_Tran_Data);
//			while(CAN_TransmitStatus(CAN1 ,box)==CAN_TxStatus_Failed);
//			/* 等待报文的发送完成*/
//			printf ("/r/n接受数据完成/r/n");
//		}
//		if(flag==1)
//		{
//			printf("/r/n接受的数据是：%d/r/n",CAN_Rece_Data.Data[0]);
//			flag =0;
//		}
	}
	#if 0
	while(1)
	{
	sg90(m);//给值0到180

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
