#include "stm32f10x.h"

#ifndef _DHT11_H
#define _DHT11_H


typedef enum{
	DHT11MODEIN =0,  // ��������
	DHT11MODEOUT=1,   //�������
}DHT11MODE;


typedef struct{
	u16 Tem;  //�¶�
	u16 Hum;  //ʪ��
}DHT11DATA_TypeDef;



#define DHT11HIGH 	(GPIO_SetBits(GPIOA,GPIO_Pin_11))
#define DHT11LOW 	(GPIO_ResetBits(GPIOA,GPIO_Pin_11))
#define ReadDHT11Pin (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11))

void DHT11Init(void);
void ChangeDHT11MODE(DHT11MODE mode);
u8 DHT11ReadData(DHT11DATA_TypeDef *dht11data);
void DHT11ERROR(void);



#endif 

