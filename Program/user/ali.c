#include "ali.h"
#include "utils_hmac.h"
#include "mqttpacket.h"
#include "usart.h"
#include "delay.h"


#define Usart1SendStrig USARTSendStr

__USART_MESSAGE usart_data={0};
_AliIOT_Connect Ali_Buf = {"\0"};
_AliData Ali_data={0};

//���������ݳ�ʼ��
void AliIOT_DataConfig(void)
{
	char Temp_buf[128] = "\0";
	memset(&Ali_Buf, 0, sizeof(_AliIOT_Connect));
	//��ȡClientID
	sprintf(Ali_Buf.ClientID, "%s|securemode=3,signmethod=hmacsha1|", Ali_DeviceName);
	Ali_Buf.ClientID_len = strlen(Ali_Buf.ClientID);
	//��ȡUserName
	sprintf(Ali_Buf.UserName, "%s&%s", Ali_DeviceName, Ali_ProductKey);
	Ali_Buf.UserName_len = strlen(Ali_Buf.UserName);
	//��ȡPassWord
	sprintf(Temp_buf, "clientId%sdeviceName%sproductKey%s", Ali_DeviceName, Ali_DeviceName, Ali_ProductKey); 
	utils_hmac_sha1(Temp_buf, strlen(Temp_buf), Ali_Buf.PassWord, Ali_DeviceSecret, strlen(Ali_DeviceSecret));
	Ali_Buf.PassWord_len = strlen(Ali_Buf.PassWord); 
	//��ȡ������IP��ַ���˿ں�
	sprintf(Ali_Buf.ServerIP, "%s.iot-as-mqtt.cn-shanghai.aliyuncs.com", Ali_ProductKey);                  //��������������
	Ali_Buf.ServerPort = 1883;
	
	//Topic�б�
	sprintf(Ali_Buf.topic_post, "/sys/%s/%s/thing/event/property/post", Ali_ProductKey, Ali_DeviceName);                 
	sprintf(Ali_Buf.topic_post_reply, "/sys/%s/%s/thing/event/property/post_reply", Ali_ProductKey, Ali_DeviceName);  
	sprintf(Ali_Buf.topic_set, "/sys/%s/%s/thing/service/property/set", Ali_ProductKey, Ali_DeviceName);  
	
//	//�������������Ϣ	
//	printf("�� �� ����%s\r\n", Ali_Buf.ServerIP);
//	printf("�˿ںţ�%s\r\n","1883");
//	printf("�ͻ���ID��%s\r\n", Ali_Buf.ClientID);   
//	printf("�� �� ����%s\r\n", Ali_Buf.UserName);   	
//	printf("��    �룺%s\r\n", Ali_Buf.PassWord);  
}


//����MQTT����
uint8_t MyMQTT_Connect(char *ClientID, char *UserName, char *PassWord)
{
	USART_ClearTxData();
	//1.����MQTT CONNECT �ṹ��
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	//2.�ṹ�帳ֵ
	data.cleansession = 1;//����Ự
	data.clientID.cstring = ClientID;//��ʼ���豸ID
	data.keepAliveInterval = 60;//���ֽ���ʱ��60s
	data.MQTTVersion = 4;//ʹ��MQTT 3.1.1
	
	data.username.cstring = UserName;//�û���
	data.password.cstring = PassWord;//�û�����
	//3.����MQTTSerialize_connect�ѽṹ���е����ݹ��ɶ�������
	usart_data.tx_count = MQTTSerialize_connect(usart_data.tx_buff, MAX_LEN,&data);
	if(usart_data.tx_count == 0)
		return 1;
	Usart1SendStrig(usart_data.tx_buff,usart_data.tx_count);
	return 0;
}

//�Ͽ�����
uint8_t MyMQTT_DisConnect(void)
{
	USART_ClearTxData();
	//1.��DISCONNECT���Ľṹ�壬��Ϊ���������ݴ��뷢�ͻ�������
	usart_data.tx_count = MQTTSerialize_disconnect(usart_data.tx_buff, MAX_LEN);
	if(usart_data.tx_count == 0)
		return 1;
	//2.���õײ����緢������
	Usart1SendStrig(usart_data.tx_buff, usart_data.tx_count);
	return 0;
}

//MQTT��������
uint8_t MyMQTT_Publish(char *topic, char *payload)
{
	uint32_t payload_len = 0;
	unsigned char dup = 0;
	int qos = 0;
	unsigned char retained = 0;
	unsigned short msgid = 0;
	
	USART_ClearTxData();
	
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = topic;//��������
	payload_len = strlen(payload);//��Ч���صĳ���
	//2.����Publish�Ķ�����������
	usart_data.tx_count = MQTTSerialize_publish(usart_data.tx_buff,MAX_LEN,dup, qos, retained, msgid,\
												topicString,(uint8_t *)payload,payload_len);
	if(usart_data.tx_count <= 0)
		return 1;
	//3.WIFI���ͳ�ȥ
	Usart1SendStrig(usart_data.tx_buff,usart_data.tx_count);
	return 0;
}


//MQTT��������
u8 MyMQTT_Subscribe(char *topic)
{
	#define TOPIC_COUNT 1
	unsigned char dup = 0;
	unsigned short msgid = 10;
	int count = TOPIC_COUNT;
	int req_qoss[TOPIC_COUNT] = {2};
	
	USART_ClearTxData();
	
	MQTTString topicStrings[TOPIC_COUNT] = { MQTTString_initializer };
	topicStrings[0].cstring = topic;
	usart_data.tx_count = MQTTSerialize_subscribe(usart_data.tx_buff, MAX_LEN, dup, msgid, count, topicStrings, req_qoss);
	
	if(usart_data.tx_count <= 0)
		return 1;
	//3.WIFI���ͳ�ȥ
	Usart1SendStrig(usart_data.tx_buff, usart_data.tx_count);
}


//MQTTȡ����������
uint8_t MyMQTT_UnSubscribe(char *topic)
{
	unsigned char dup = 0;
	unsigned short msgid = 0;

	USART_ClearTxData();
	
	MQTTString topicStrings = MQTTString_initializer ;
	
	topicStrings.cstring = topic;
	usart_data.tx_count = MQTTSerialize_unsubscribe(usart_data.tx_buff, MAX_LEN, dup, msgid, 1, &topicStrings);
	
	if(usart_data.tx_count <= 0)
		return 1;
	//3.WIFI���ͳ�ȥ
	Usart1SendStrig(usart_data.tx_buff, usart_data.tx_count);
	return 0;
}




void USART_ClearTxData(void)
{
	memset(usart_data.tx_buff, 0, sizeof(usart_data.tx_buff));
	usart_data.tx_count = 0;
}














