#ifndef _USART_H
#define _USART_H

#include "user_code.h"

void usart_cfg(void);
void usart1_cfg(void);

void USART_sendChar(USART_TypeDef* USARTx, char ch);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif
