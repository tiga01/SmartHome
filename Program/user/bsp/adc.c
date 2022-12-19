#include "adc.h"
#include "stm32f10x.h"


/*
�������ܣ�ADC���������ʼ��
������������
��������ֵ����
*/
void ADCInit(void)
{
	
	GPIO_InitTypeDef g;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1,ENABLE);
	g.GPIO_Pin = GPIO_Pin_1;		
	g.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&g);	
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //����ADC��Ƶ����6 PCLK2(72M)/6=12,ADC_CLK���Ƶ�ʲ��ܳ���14M
	//ADC������
	ADC_InitTypeDef a;
	a.ADC_ContinuousConvMode = DISABLE;  //����ת��
	a.ADC_DataAlign = ADC_DataAlign_Right;  //�Ҷ���
	a.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //
	a.ADC_Mode = ADC_Mode_Independent;
	
	a.ADC_NbrOfChannel = 1; //˳����й���ת����ADCͨ������Ŀ
	a.ADC_ScanConvMode = DISABLE;  //��������ģʽ
	ADC_Init(ADC1,&a);
	
	//ͨ������
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1,ENABLE);
}



/*
�������ܣ���ȡ��������ADC����
�����������޲�
��������ֵ�� ADC��ֵ
*/
u16 GetADCValue(void)
{
	u16 value = 0;
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET)
	{
	}
	value = ADC_GetConversionValue(ADC1);
	
	
	
	return value;
}
