#include "stm32f10x.h"
#include "dht11.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"

//extern 	DHT11DATA_TypeDef dht11={0};


/*
�������ܣ���ʼ��DHT11
�����������޲�
��������ֵ���޷�
*/
void DHT11Init(void)
{
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //ʹ��ʱ��
	g.GPIO_Pin = GPIO_Pin_11;		
	g.GPIO_Mode = GPIO_Mode_Out_PP;   //ͨ���������
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&g);
	GPIO_SetBits(GPIOA,GPIO_Pin_11);  //��1
}

/*
�������ܣ��ı�DHT11�Ĺ���ģʽ
����������mode :  DHT11MODEOUT :ͨ���������
									DHT11MODEIN �� ��������
��������ֵ���޷�
*/
void ChangeDHT11MODE(DHT11MODE mode)
{
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //ʹ��ʱ��
	g.GPIO_Pin = GPIO_Pin_11;			 
	g.GPIO_Speed = GPIO_Speed_50MHz;	
	if(mode == DHT11MODEOUT)
	{
		 g.GPIO_Mode = GPIO_Mode_Out_PP;   //ͨ���������
	}
	else if (mode == DHT11MODEIN)
	{
		g.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	}
	GPIO_Init(GPIOA,&g);
}

/*
�������ܣ���ȡ��ʪ������
����������dht11data��DHT11����ʪ������
��������ֵ���޷�
*/
u8 DHT11ReadData(DHT11DATA_TypeDef *dht11data)
{
	u8 i =0,timeout=0;
	u8 data[5] = {0};

	ChangeDHT11MODE(DHT11MODEOUT);
	DHT11HIGH;
		//1.������ʼ�ź�
	DHT11LOW;
	Delaynms(18);
	DHT11HIGH;
	//2.�ȴ�DHT11��Ӧ
	ChangeDHT11MODE(DHT11MODEIN);
	//�ȴ���Ӧ�͵�ƽ����   ����
	while(ReadDHT11Pin == 1)
	{
		timeout++;
		Delaynus(1);
		if(timeout >100){
			return 1;
		}
	}
	timeout =0 ;
	//3.�ȴ���Ӧ�ߵ�ƽ����
		while(ReadDHT11Pin == 0)
	{
		timeout++;
		Delaynus(1);
		if (timeout >100){
			return 2;
		}
	}
	timeout =0;
	//ѭ������40λ������
	for(i=0;i<40;i++)
	{
	//�ȴ����ݵ͵�ƽ����
		while(ReadDHT11Pin ==1)
		{
		timeout++;
		Delaynus(1);
		if (timeout >100){
			return 3;
		}
		}
		timeout = 0;
		//�ȴ����ݸߵ�ƽ����
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
		//��ʱ30΢�������������0����1
		if(ReadDHT11Pin == 1)
		{
			data[i/8] |=(1<<(7-i%8));
		}
		else //����0
		{
			data[i/8] &=(~1<<(7-i%8));
		}		

	}
	//4.�����ź�
	Delaynus(54);
	ChangeDHT11MODE(DHT11MODEOUT);
	//5.У��
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
�������ܣ�ΪDHT11�ṩ������������
�����������޲�
��������ֵ���޷�
*/
void DHT11ERROR(void)
{
	u8 ret;  
	
//	 ret = DHT11ReadData(&dht11);
	
	while (ret ==0){
	
			switch(ret){
//			case '0' :
//				printf("DHT11�������У�");
//			continue;
			case '1' :
				printf("�ȴ���Ӧ�͵�ƽ����");
			break;
			case '2' :
				printf("�ȴ���Ӧ�ߵ�ƽ����");
			break;
			case '3' :
				printf("�ȴ����ݵ͵�ƽ����");
			break;
			case '4' :
				printf("�ȴ����ݸߵ�ƽ����");
			break;
			case '5' :
				printf("����У��ͷ�������");
			break;
//			default :
//				printf("δ֪���ʹ���");
//			break;
		}
	}
		printf("DHT11����������ף˳����\r\n");
}


