#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"

//#define KEY1 GPIOC->ODR&=~(1<<0)
//#define KEY2 GPIOC->ODR&=~(1<<1)

#define KEY1 (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))
#define KEY2 (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1))



void KeyInit(void);
u8 KeyScan1(void);
u8 KeyScan2(void);

#endif

