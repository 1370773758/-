/****************************************************************
      ----mode--- 
      0.��������
		  1.ǳɫ��ɨ��
			2.��ɫ��ɨ��
			3.���ڵȴ��˻�����ģʽ��״̬
			21.ǳɫɨ��
	   	22.��ɫɨ��
			23.�ж��Ƿ�Ҫ��������ֵ��ִ�в��˳�������ģʽ
****************************************************************/
#include "BSP.h"
#include "stmflash.h"

extern u8 mode;
extern u16 threshold_value[16];
extern u16 count;
s8 n;

int main(void)
{	

  SystemInit();
	Systick_Configuration();//ʱ��ѡ���ⲿ8Mhz
	STMFLASH_Read(FLASH_SAVE_ADDR,threshold_value,16);
  BSP_Configuration();
	while(1)
	{
		if(mode==0&&KEY==1)
			{
				LED0=1;
			  SysDelay_ms(80);
				LED0=0;
			  SysDelay_ms(80);
				LED0=1;
			  SysDelay_ms(80);
				LED0=0;
			  SysDelay_ms(1000);
			}
		else if(mode==21)	
			{
				for(n=0;n<2;n++)
				{
					LED6=!LED6;
					SysDelay_ms(50);
					LED7=LED6;
					SysDelay_ms(50);
					LED8=LED7;
					SysDelay_ms(50);
					LED9=LED8;
					SysDelay_ms(50);
					LED10=LED9;
					SysDelay_ms(50);
				}
				for(n=0;n<2;n++)
				{
					LED10=!LED10;
					SysDelay_ms(50);
					LED9=LED10;
					SysDelay_ms(50);
					LED8=LED9;
					SysDelay_ms(50);
					LED7=LED8;
					SysDelay_ms(50);
					LED6=LED7;
					SysDelay_ms(50);
				}
			}
		else if(mode==22)	
			{
				for(n=0;n<2;n++)
				{
					LED5=!LED5;
					LED11=!LED11;
					SysDelay_ms(50);
					LED4=LED5;
					LED12=LED11;
					SysDelay_ms(50);
					LED3=LED4;
					LED13=LED12;
					SysDelay_ms(50);
					LED2=LED3;
					LED14=LED13;
					SysDelay_ms(50);
					LED1=LED2;
					LED15=LED14;
					SysDelay_ms(50);
				}
				for(n=0;n<2;n++)
				{
					LED1=!LED1;
					LED15=!LED15;
					SysDelay_ms(50);
					LED2=LED1;
					LED14=LED15;
					SysDelay_ms(50);
					LED3=LED2;
					LED13=LED14;
					SysDelay_ms(50);
					LED4=LED3;
					LED12=LED13;
					SysDelay_ms(50);
					LED5=LED4;
					LED11=LED12;
					SysDelay_ms(50);
				}		
			}
	}
}

