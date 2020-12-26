#ifndef _CAN_H
#define _CAN_H

#include "user_code.h"

#define PASS_ID ((uint32_t)0x1314)

extern CanRxMsg  CAN_Rece_Data;
extern CanTxMsg	CAN_Tran_Data;

extern u8 flag;

void can_cfg(void);

#endif
