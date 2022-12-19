#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

//#define LED1ON  (GPIOC->ODR &=~(1<<8))
//#define LED1OFF (GPIOC->ODR |=(1<<8))

//#define LED2ON  (GPIOC->ODR &=~(1<<9))
//#define LED2OFF (GPIOC->ODR |=(1<<9))

#define LED1ON  GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define LED1OFF GPIO_SetBits(GPIOC,GPIO_Pin_8)

#define LED1 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8)
#define LED2 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)



#define LED2ON  GPIO_ResetBits(GPIOC,GPIO_Pin_9)
#define LED2OFF GPIO_SetBits(GPIOC,GPIO_Pin_9)


#define LED1TOGGLE  (GPIOC->ODR ^=(1<<8))
#define LED2TOGGLE  (GPIOC->ODR ^=(1<<9))

#define GPIOLED1  GPIO_Pin_8
#define GPIOLED2 GPIO_Pin_9


#endif

void LEDInit(void);

