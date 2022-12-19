#ifndef __ALI_H
#define __ALI_H

#include "stm32f10x.h"

//{
//  "ProductKey": "hrmjkE2JDPJ",
//  "DeviceName": "HomeDevice",
//  "DeviceSecret": "8f279e9b52a0f1317b68ce629ffb29a2"
//}

//��Ԫ��
//�滻Ϊ�Լ�����Ԫ��
#define Ali_ProductKey 		"hrmjkE2JDPJ"
#define Ali_DeviceName 		"HomeDevice"
#define Ali_DeviceSecret 	"8f279e9b52a0f1317b68ce629ffb29a2"

#define ALIBUF_SIZE 256

typedef struct{
	char ClientID[ALIBUF_SIZE];
	uint16_t ClientID_len;
	char UserName[ALIBUF_SIZE];
	uint16_t UserName_len;
	char PassWord[ALIBUF_SIZE];
	uint16_t PassWord_len;
	char ServerIP[ALIBUF_SIZE];
	uint16_t ServerPort;
	
	char topic_post[ALIBUF_SIZE];//����Topic
	char topic_post_reply[ALIBUF_SIZE];//���Ļش���Ӧ
	char topic_set[ALIBUF_SIZE];//����������Ϣ
}_AliIOT_Connect;
extern _AliIOT_Connect Ali_Buf;

/* ������ͨ�����ݷ�װ */
typedef struct
{
	uint16_t Tem;
	uint16_t Hum;
	uint16_t Light;
	u8 Led1;
	u8 Led2;
}_AliData;


#define MAX_LEN 1024


typedef struct{
	uint16_t rx_time;								//���ճ�ʱ����
	uint8_t tx_buff[MAX_LEN];
	uint32_t tx_count;
}__USART_MESSAGE;
extern __USART_MESSAGE usart_data;


extern _AliData Ali_data;

void AliIOT_DataConfig(void);
uint8_t MyMQTT_Connect(char *ClientID, char *UserName, char *PassWord);
uint8_t MyMQTT_Publish(char *topic, char *payload);
uint8_t MyMQTT_Subscribe(char *topic);
uint8_t MyMQTT_UnSubscribe(char *topic);

uint8_t MyMQTT_DisConnect(void);

void USART_ClearTxData(void);


#endif

