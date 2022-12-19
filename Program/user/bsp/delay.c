#include "delay.h"


/*
	函数功能：滴答定时器初始化，每隔一毫秒产生一次中断
	函数参数：无
	函数返回值：无
*/
void DelayInit(void)
{
	SysTick_Config(40000);
		
}


/*
	函数功能：1微妙延时
	函数参数：无
	函数返回值：无
*/
void Delay1us(void)
{
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
}

/*
	函数功能：n微妙延时
  函数参数：time:延时的微秒数
	函数返回值：无
*/
void Delaynus(u32 time)
{
	while(time--)
	{
		Delay1us();
	}
}

/*
	函数功能：毫秒延时
  函数参数：time:延时的毫秒数
	函数返回值：无
*/
void Delaynms(u32 time)
{
	while(time--)
	{
		Delaynus(1000);
	}
}

/*
函数功能：秒延时
函数参数：time ：延时的秒数
函数返回值：无反
*/
void Delayns(u32 time)
{
	while(time--){
		Delaynms(1000);
	}
}
