#include "delay.h"


/*
	�������ܣ��δ�ʱ����ʼ����ÿ��һ�������һ���ж�
	������������
	��������ֵ����
*/
void DelayInit(void)
{
	SysTick_Config(40000);
		
}


/*
	�������ܣ�1΢����ʱ
	������������
	��������ֵ����
*/
void Delay1us(void)
{
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
}

/*
	�������ܣ�n΢����ʱ
  ����������time:��ʱ��΢����
	��������ֵ����
*/
void Delaynus(u32 time)
{
	while(time--)
	{
		Delay1us();
	}
}

/*
	�������ܣ�������ʱ
  ����������time:��ʱ�ĺ�����
	��������ֵ����
*/
void Delaynms(u32 time)
{
	while(time--)
	{
		Delaynus(1000);
	}
}

/*
�������ܣ�����ʱ
����������time ����ʱ������
��������ֵ���޷�
*/
void Delayns(u32 time)
{
	while(time--){
		Delaynms(1000);
	}
}
