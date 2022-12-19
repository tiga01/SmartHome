#include "usart.h"
#include "stdio.h"
#include "stm32f10x.h"
/*
�������ܣ�����1��ʼ��
����������baud  --������
��������ֵ���޷�
*/
void USART1Init(u32 bound)
{

//	USARTx_DR =data;  //���ݷ���
//	dat = USARTx_DR;  //���ݽ���
/*
	USART_CR1
	USART_BRR
	
	 //1.ʹ��PA�˿�ʱ��
	RCC->APB2ENR |=(1<<4);
	//2.PC8/9���ó�ͨ���������
	GPIOC->CRH&=~(0xf<<0); //����  ���Ĵ�������Ĭ�ϵ���ֵ��Ϊ0	
	GPIOC->CRH&= ~(0xf<<4);	//����  ���Ĵ�������Ĭ�ϵ���ֵ��Ϊ0
	GPIOC->CRH|=(0x3<<0);  //��Ĵ���д��0011������PA9����Ϊͨ��GPIO
	GPIOC->CRH|=(0x3<<4); //��Ĵ���д��0011������PA10����Ϊͨ��GPIO
*/
	
	//ʹ��ʱ��
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
//����PA9 �����������
	g.GPIO_Pin = GPIO_Pin_9;		
	g.GPIO_Mode = GPIO_Mode_AF_PP;
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&g);
	//����PA10 ��������
	g.GPIO_Pin = GPIO_Pin_10;		
	g.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&g);
	
	//���ô���	
	
	USART_InitTypeDef u;  //��ʼ���ṹ��

	u.USART_BaudRate = bound;//һ������Ϊ9600;
	u.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	u.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	u.USART_Parity = USART_Parity_No;//����żУ��λ
	u.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	u.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &u); //��ʼ������
	
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	//ʹ�ܴ���
  USART_Cmd(USART1, ENABLE);    
	
}
/*
�������ܣ����͵����ֽ�����
������������Ҫ���͵��ֽ�
��������ֵ���޷�
*/
void USARTSendByte(u8 data)
{
//�ж����ݷ����Ƿ����
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0)
	{
	}	
	USART_SendData(USART1,data);
}
/*
�������ܣ������ַ���
����������*p����Ҫ���͵��ַ�����len���ַ�������
��������ֵ���޷�
*/
void USARTSendStr(u8 *p,u32 len)
{
	u32 i =0;
	for(i=0;i<len;i++)
	{
		USARTSendByte(p[i]);
	}
}

//���¶���fputc������ʹ��printf
int fputc(int c, FILE * stream)
{      
  USARTSendByte(c);     
	return c;
}
