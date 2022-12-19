#include "key.h"
#include "delay.h"

/*
函数功能：按键初始化
函数参数：无
函数返回值：无
*/
void KeyInit(void)
{
	/*
	//1.使能PC端口时钟
	RCC->APB2ENR |=(1<<4);
	//2.PC0/1配置成通用推挽输出
	GPIOC->CRL &=~(0xf<<0); //清零  将寄存器里面默认的数值变为0	
	GPIOC->CRL &=~(0xf<<4);	//清零  将寄存器里面默认的数值变为0
	GPIOC->CRL |=(0x4<<0);  //向寄存器写入0011，即将PC8配置为浮空输入
	GPIOC->CRL|=(0x4<<4);  //向寄存器写入0011，即将PC9配置为浮空输入
	//3.PC0/1 输出0
	GPIOC->ODR &=~(1<<0);
	GPIOC->ODR &=~(1<<1);
*/
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	g.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0 ;		
	g.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&g);	
}

/*
函数功能：按键扫描
函数参数：无
函数返回值：高电平
*/
u8 KeyScan1(void)
{
  u8 keyvalue=0;
  if(KEY1==0) //按键按下
  {
    Delaynms(10); //延时消抖
    if(KEY1==0)//判断按键真的按下
    {
      while(KEY1==0)//松手检测
      {
      }
      keyvalue=1;
    }
  }
  return keyvalue;
}


u8 KeyScan2(void)
{
  u8 keyvalue=0;
  if(KEY2==0) //按键按下
  {
    Delaynms(10); //延时消抖
    if(KEY2==0)//判断按键真的按下
    {
      while(KEY2==0)//松手检测
      {
      }
      keyvalue = 1;
    }
  }
  return keyvalue;
}

