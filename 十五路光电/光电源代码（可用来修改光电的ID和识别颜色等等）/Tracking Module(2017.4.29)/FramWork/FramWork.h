#ifndef __FRAMWORK_H
#define __FRAMWORK_H

#include "BSP.h"


typedef struct
{
		u16 data1[9];
		u16 data2[9];
		u16 data3[9];
		u16 data4[9];
		u16 data5[9];
		u16 data6[9];
		u16 data7[9];
		u16 data8[9];
		u16 data9[9];
		u16 data10[9];
		u16 data11[9];
		u16 data12[9];
		u16 data13[9];
		u16 data14[9];
		u16 data15[9];
		u16 data16[9];
}adc_data_type;

void DevelopmentFramwork(void);
void assign_values(u16 *send_data,u16 *receive_data,char count);
u16 mid_data(u16 *data,char count);

#endif

