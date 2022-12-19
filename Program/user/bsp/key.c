#include "key.h"
#include "delay.h"

/*
�������ܣ�������ʼ��
������������
��������ֵ����
*/
void KeyInit(void)
{
	/*
	//1.ʹ��PC�˿�ʱ��
	RCC->APB2ENR |=(1<<4);
	//2.PC0/1���ó�ͨ���������
	GPIOC->CRL &=~(0xf<<0); //����  ���Ĵ�������Ĭ�ϵ���ֵ��Ϊ0	
	GPIOC->CRL &=~(0xf<<4);	//����  ���Ĵ�������Ĭ�ϵ���ֵ��Ϊ0
	GPIOC->CRL |=(0x4<<0);  //��Ĵ���д��0011������PC8����Ϊ��������
	GPIOC->CRL|=(0x4<<4);  //��Ĵ���д��0011������PC9����Ϊ��������
	//3.PC0/1 ���0
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
�������ܣ�����ɨ��
������������
��������ֵ���ߵ�ƽ
*/
u8 KeyScan1(void)
{
  u8 keyvalue=0;
  if(KEY1==0) //��������
  {
    Delaynms(10); //��ʱ����
    if(KEY1==0)//�жϰ�����İ���
    {
      while(KEY1==0)//���ּ��
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
  if(KEY2==0) //��������
  {
    Delaynms(10); //��ʱ����
    if(KEY2==0)//�жϰ�����İ���
    {
      while(KEY2==0)//���ּ��
      {
      }
      keyvalue = 1;
    }
  }
  return keyvalue;
}

