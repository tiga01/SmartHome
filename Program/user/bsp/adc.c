#include "adc.h"
#include "stm32f10x.h"


/*
函数功能：ADC光敏电阻初始化
函数参数：无
函数返回值：无
*/
void ADCInit(void)
{
	
	GPIO_InitTypeDef g;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1,ENABLE);
	g.GPIO_Pin = GPIO_Pin_1;		
	g.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&g);	
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置ADC分频因子6 PCLK2(72M)/6=12,ADC_CLK最大频率不能超过14M
	//ADC的配置
	ADC_InitTypeDef a;
	a.ADC_ContinuousConvMode = DISABLE;  //单次转换
	a.ADC_DataAlign = ADC_DataAlign_Right;  //右对齐
	a.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //
	a.ADC_Mode = ADC_Mode_Independent;
	
	a.ADC_NbrOfChannel = 1; //顺序进行规则转换的ADC通道的数目
	a.ADC_ScanConvMode = DISABLE;  //独立工作模式
	ADC_Init(ADC1,&a);
	
	//通道排序
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1,ENABLE);
}



/*
函数功能：获取光敏电阻ADC数据
函数参数：无参
函数返回值： ADC数值
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
