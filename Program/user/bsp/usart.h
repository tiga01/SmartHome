#include "stm32f10x.h"

#ifndef _USART_H
#define _USART_H


void USART1Init(u32 bound);
void USARTSendByte(u8 data);
void USARTSendStr(u8 *p,u32 len);


#endif
