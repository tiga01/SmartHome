
#include "led.h"

/*

函数功能：LED灯初始化
函数参数：无反
函数返回值：无参
*/
void LEDInit(void)
{
	/*
 //1.使能PC端口时钟
	RCC->APB2ENR |=(1<<4);
	//2.PC8/9配置成通用推挽输出
	GPIOC->CRH&=~(0xf<<0); //清零  将寄存器里面默认的数值变为0	
	GPIOC->CRH&= ~(0xf<<4);	//清零  将寄存器里面默认的数值变为0
	GPIOC->CRH|=(0x3<<0);  //向寄存器写入0011，即将PC8配置为通用GPIO
	GPIOC->CRH|=(0x3<<4);  //向寄存器写入0011，即将PC9配置为通用GPIO
	//3.PC8/9 输出0
	GPIOC->ODR &=~(1<<8);
	GPIOC->ODR &=~(1<<9);
*/
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	g.GPIO_Pin = GPIOLED1 | GPIOLED2;		
	g.GPIO_Mode = GPIO_Mode_Out_PP;
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&g);
	LED1OFF;
	LED2OFF;
	
}

