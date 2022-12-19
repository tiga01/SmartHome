#include "usart.h"
#include "stdio.h"
#include "stm32f10x.h"
/*
函数功能：串口1初始化
函数参数：baud  --波特率
函数返回值：无反
*/
void USART1Init(u32 bound)
{

//	USARTx_DR =data;  //数据发送
//	dat = USARTx_DR;  //数据接收
/*
	USART_CR1
	USART_BRR
	
	 //1.使能PA端口时钟
	RCC->APB2ENR |=(1<<4);
	//2.PC8/9配置成通用推挽输出
	GPIOC->CRH&=~(0xf<<0); //清零  将寄存器里面默认的数值变为0	
	GPIOC->CRH&= ~(0xf<<4);	//清零  将寄存器里面默认的数值变为0
	GPIOC->CRH|=(0x3<<0);  //向寄存器写入0011，即将PA9配置为通用GPIO
	GPIOC->CRH|=(0x3<<4); //向寄存器写入0011，即将PA10配置为通用GPIO
*/
	
	//使能时钟
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
//配置PA9 复用推挽输出
	g.GPIO_Pin = GPIO_Pin_9;		
	g.GPIO_Mode = GPIO_Mode_AF_PP;
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&g);
	//配置PA10 浮空输入
	g.GPIO_Pin = GPIO_Pin_10;		
	g.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&g);
	
	//配置串口	
	
	USART_InitTypeDef u;  //初始化结构体

	u.USART_BaudRate = bound;//一般设置为9600;
	u.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	u.USART_StopBits = USART_StopBits_1;//一个停止位
	u.USART_Parity = USART_Parity_No;//无奇偶校验位
	u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART1, &u); //初始化串口
	
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	//使能串口
  USART_Cmd(USART1, ENABLE);    
	
}
/*
函数功能：发送单个字节数据
函数参数：需要发送的字节
函数返回值：无反
*/
void USARTSendByte(u8 data)
{
//判断数据发送是否完成
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0)
	{
	}	
	USART_SendData(USART1,data);
}
/*
函数功能：发送字符串
函数参数：*p：需要发送的字符串，len：字符串长度
函数返回值：无反
*/
void USARTSendStr(u8 *p,u32 len)
{
	u32 i =0;
	for(i=0;i<len;i++)
	{
		USARTSendByte(p[i]);
	}
}

//重新定义fputc函数，使能printf
int fputc(int c, FILE * stream)
{      
  USARTSendByte(c);     
	return c;
}
