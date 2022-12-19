
#include "led.h"

/*

�������ܣ�LED�Ƴ�ʼ��
�����������޷�
��������ֵ���޲�
*/
void LEDInit(void)
{
	/*
 //1.ʹ��PC�˿�ʱ��
	RCC->APB2ENR |=(1<<4);
	//2.PC8/9���ó�ͨ���������
	GPIOC->CRH&=~(0xf<<0); //����  ���Ĵ�������Ĭ�ϵ���ֵ��Ϊ0	
	GPIOC->CRH&= ~(0xf<<4);	//����  ���Ĵ�������Ĭ�ϵ���ֵ��Ϊ0
	GPIOC->CRH|=(0x3<<0);  //��Ĵ���д��0011������PC8����Ϊͨ��GPIO
	GPIOC->CRH|=(0x3<<4);  //��Ĵ���д��0011������PC9����Ϊͨ��GPIO
	//3.PC8/9 ���0
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

