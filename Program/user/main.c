#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "dht11.h"
#include "stdio.h"
#include "stm32f10x_it.h"
#include "adc.h"
#include "ali.h"
#include "lcd.h"

int main(void)
{
	u8 key1=0;
	u16 Tem1 = 20;   //�¶���ֵ ��λΪ25��
//	u16 Hum1 = 80;   //ʪ����ֵ  ��λΪ %
	u16 lightvalue = 0;
	char jsonbuff[512]={0};
	
	
	char showTem[36]={0};
	char showHum[36]={0};
	char showlightvalue[36]={0};
	
	extern const unsigned char gImage_tu[2760];
	extern const unsigned char gImage_Hum[520];
	extern const unsigned char gImage_Tem[520];
	extern const unsigned char gImage_sun[520];

	DHT11DATA_TypeDef dht11={0};


	//��ʼ������
	LEDInit();
	KeyInit();
	USART1Init(57600);  //һ��Ϊ9600/38400/115200
	DHT11Init();
	DelayInit();
	ADCInit();
	
	
	AliIOT_DataConfig();
	printf("����ת�������������� \r\n");
	Delaynms(200);
	
	//ʹ��MQTTЭ�����Ӱ�����Э��
	MyMQTT_Connect(Ali_Buf.ClientID,Ali_Buf.UserName,Ali_Buf.PassWord);
	//���ܺ���
  //DHT11ERROR();    //DHT11����������ͣ������У�
	LCD_Init();
//	LCD_ShowString(10,20,16,(u8*)"helloworld",0);
	Show_Str(46,0,RED,WHITE,(u8*)"�����ƼҾ�",32,0);  
	Show_Str(0,60,BLACK,WHITE,(u8*)"��    ��:",16,0);  
	Show_Str(0,100,BLACK,WHITE,(u8*)"ʪ    ��:",16,0); 
	Show_Str(0,140,BLACK,WHITE,(u8*)"����ǿ��:",16,0);  
  
	Show_Str(90,100,BLUE,WHITE,(u8*)"    %",16,0); 
	Show_Str(90,140,GREEN,WHITE,(u8*)"    lx",16,0);  



	Paint_Bmp(0,0,43,32,gImage_tu);
	Paint_Bmp(160,60,16,16,gImage_Tem);
	Paint_Bmp(160,100,16,16,gImage_Hum);
	Paint_Bmp(160,140,16,16,gImage_sun);

	
	while(1)
	{	
		
			if (alitime[0] > alitime[1])
		{
		
			Ali_data.Tem = dht11.Tem ;
			Ali_data.Hum = dht11.Hum ;
			Ali_data.Light = lightvalue ;
			Ali_data.Led1 = LED1 ;
			Ali_data.Led2 = LED2 ;
			sprintf(jsonbuff,"{\
				\"id\":1669098522277,\
				\"params\":{\
        \"temperature\":%d,\
        \"Humidity\":%d,\
        \"LightLux\":%d,\
		    \"LED1\":%d,\
			\"LED2\":%d\
				},\
    \"version\":\"1.0\",\
   \"method\":\"thing.event.property.post\"}",
			Ali_data.Tem,Ali_data.Hum,Ali_data.Light,Ali_data.Led1,Ali_data.Led2);
			//ʹ��MQTTЭ�鷢��ָ������
			MyMQTT_Publish(Ali_Buf.topic_post,jsonbuff);
			
			alitime[0]=0;
		}
		
		
		Delaynms(1);
		if (dht11time >100)   //ʵ��ʹ��Ӧ2s���һ�Σ�������󣬼�dht11>20000
		{
		DHT11ReadData(&dht11);	
//		printf("Tem=%d,Hum =%d\r\n",dht11.Tem,dht11.Hum);
		dht11time =0;
		}
//		if (ledtime >100)
//		{
//		LED1TOGGLE;
//		ledtime =0;
//		}
		

		sprintf(showTem,"%d   ��",dht11.Tem);
		Show_Str(86,60,RED,WHITE,(u8 *)showTem,16,0);
		
		sprintf(showHum,"%d",dht11.Hum);
		Show_Str(86,100,BLUE,WHITE,(u8 *)showHum,16,0);

		
		if (adctime[0] > adctime[1])
		{
			lightvalue = GetADCValue();
			
//			printf("lightvalue=%d\r\n",lightvalue);
				sprintf(showlightvalue,"%d",lightvalue);
				Show_Str(80,140,GREEN,WHITE,(u8 *)showlightvalue,16,0);
				adctime[0]=0;
		}
		
		
		
		
		if (ledtime>50)
		{
			//�¶ȴ�����ֵ LED1��
			if (dht11.Tem > Tem1)
			{
				led2time[1] = 50;
				LED1ON;
			}
			//�¶�С����ֵ��LED1�Ʋ���
			else
			{
				led2time[1] = 200;
				LED1OFF;
			}
			ledtime = 0;
		}
		if(led2time[0] > led2time[1])
	{
		LED2TOGGLE;
		led2time[0] =0 ;
	}
		

		
//		if (dht11.Hum > Hum1 & dht11.Tem > Tem1)  //�¶Ȼ�ʪ�ȴ�����ֵ��LED1��
//		{
//			LED1ON;
//			LED2ON;
//			Delaynms(50);
//			LED2OFF;
//		}
//		if(dht11.Tem < Tem1 & dht11.Hum < Hum1)    //С����ֵ��LED1��
//		{
//			LED1OFF;
//			LED2ON;
//			Delaynms(200);
//			LED2OFF;
//		}
//		
		if (key1 == 1){			
		
			
		}
			
	 key1 = KeyScan1();
		
	}
}
