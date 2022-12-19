#include "stm32f10x.h"
#include "dht11.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"

//extern 	DHT11DATA_TypeDef dht11={0};


/*
函数功能：初始化DHT11
函数参数：无参
函数返回值：无反
*/
void DHT11Init(void)
{
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //使能时钟
	g.GPIO_Pin = GPIO_Pin_11;		
	g.GPIO_Mode = GPIO_Mode_Out_PP;   //通用推挽输出
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&g);
	GPIO_SetBits(GPIOA,GPIO_Pin_11);  //置1
}

/*
函数功能：改变DHT11的工作模式
函数参数：mode :  DHT11MODEOUT :通用推挽输出
									DHT11MODEIN ： 浮空输入
函数返回值：无反
*/
void ChangeDHT11MODE(DHT11MODE mode)
{
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //使能时钟
	g.GPIO_Pin = GPIO_Pin_11;			 
	g.GPIO_Speed = GPIO_Speed_50MHz;	
	if(mode == DHT11MODEOUT)
	{
		 g.GPIO_Mode = GPIO_Mode_Out_PP;   //通用推挽输出
	}
	else if (mode == DHT11MODEIN)
	{
		g.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	}
	GPIO_Init(GPIOA,&g);
}

/*
函数功能：读取温湿度数据
函数参数：dht11data：DHT11的温湿度数据
函数返回值：无反
*/
u8 DHT11ReadData(DHT11DATA_TypeDef *dht11data)
{
	u8 i =0,timeout=0;
	u8 data[5] = {0};

	ChangeDHT11MODE(DHT11MODEOUT);
	DHT11HIGH;
		//1.发送起始信号
	DHT11LOW;
	Delaynms(18);
	DHT11HIGH;
	//2.等待DHT11响应
	ChangeDHT11MODE(DHT11MODEIN);
	//等待响应低电平到来   死等
	while(ReadDHT11Pin == 1)
	{
		timeout++;
		Delaynus(1);
		if(timeout >100){
			return 1;
		}
	}
	timeout =0 ;
	//3.等待响应高电平到来
		while(ReadDHT11Pin == 0)
	{
		timeout++;
		Delaynus(1);
		if (timeout >100){
			return 2;
		}
	}
	timeout =0;
	//循环接收40位的数据
	for(i=0;i<40;i++)
	{
	//等待数据低电平到来
		while(ReadDHT11Pin ==1)
		{
		timeout++;
		Delaynus(1);
		if (timeout >100){
			return 3;
		}
		}
		timeout = 0;
		//等待数据高电平到来
		while(ReadDHT11Pin ==0)
		{
		timeout++;
		Delaynus(1);
		if (timeout >100){
			return 4;
		}
		}
		timeout = 0;
		Delaynus(30);
		//延时30微秒后，区分数据是0还是1
		if(ReadDHT11Pin == 1)
		{
			data[i/8] |=(1<<(7-i%8));
		}
		else //数据0
		{
			data[i/8] &=(~1<<(7-i%8));
		}		

	}
	//4.结束信号
	Delaynus(54);
	ChangeDHT11MODE(DHT11MODEOUT);
	//5.校验
	if (data[4] == (data[0]+data[1] +data[2]+data[3]))
	{
		dht11data ->Hum = data[0];
		dht11data ->Tem = data[2];
		return 0;
	}
	else
	{
		return 5;
	}
}

/* 
函数功能：为DHT11提供报错类型提醒
函数参数：无参
函数返回值：无反
*/
void DHT11ERROR(void)
{
	u8 ret;  
	
//	 ret = DHT11ReadData(&dht11);
	
	while (ret ==0){
	
			switch(ret){
//			case '0' :
//				printf("DHT11正常运行！");
//			continue;
			case '1' :
				printf("等待响应低电平错误！");
			break;
			case '2' :
				printf("等待响应高电平错误！");
			break;
			case '3' :
				printf("等待数据低电平错误！");
			break;
			case '4' :
				printf("等待数据高电平错误！");
			break;
			case '5' :
				printf("数据校验和发生错误！");
			break;
//			default :
//				printf("未知类型错误！");
//			break;
		}
	}
		printf("DHT11工作正常，祝顺利！\r\n");
}


