#include "FramWork.h"
#include "math.h"
#include "BSP.h"

extern unsigned char sbus_rx_buffer[28];
adc_data_type adc_data_typedef;
u16 data_rank[9];
u16 adc_data[16];


void DevelopmentFramwork(void)
{
	assign_values(adc_data_typedef.data1,data_rank,9);
	adc_data[0]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data2,data_rank,9);
	adc_data[1]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data3,data_rank,9);
	adc_data[2]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data4,data_rank,9);
	adc_data[3]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data5,data_rank,9);
	adc_data[4]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data6,data_rank,9);
	adc_data[5]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data7,data_rank,9);
	adc_data[6]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data8,data_rank,9);
	adc_data[7]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data9,data_rank,9);
	adc_data[8]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data10,data_rank,9);
	adc_data[9]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data11,data_rank,9);
	adc_data[10]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data12,data_rank,9);
	adc_data[11]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data13,data_rank,9);
	adc_data[12]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data14,data_rank,9);
	adc_data[13]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data15,data_rank,9);
	adc_data[14]=mid_data(data_rank,9);
	
	assign_values(adc_data_typedef.data16,data_rank,9);
	adc_data[15]=mid_data(data_rank,9);
}

void assign_values(u16 *send_data,u16 *receive_data,char count)				//将一个数组的值赋给另外一个数组
{
	char cir;
	for(cir=0;cir<count;cir++)
	{
		receive_data[cir]=send_data[cir];
	}

}
	
u16 mid_data(u16 *data,char count)						//中值滤波
{
	char cir,cir1;
	char num;
	u16 swap_data;
	num=(count+1)/2;
	for(cir=0;cir<num;cir++)
	{
		for(cir1=count;cir1>cir;cir1--)
		{
			if(data[cir1]>data[cir1-1])
			{
				swap_data=data[cir1-1];
				data[cir1-1]=data[cir1];
				data[cir1]=swap_data;
			}
		}
	}
	return data[num-1];
}







