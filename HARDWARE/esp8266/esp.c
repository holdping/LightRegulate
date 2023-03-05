#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "esp.h"
#include "usart3.h"
#include "bsp_adc.h"
#include "led.h"

extern char RECS[600];
extern char RECS1[600];
const char* WIFI ="test";
const char* WIFIASSWORD="80808080";
const char* ClintID="e455919db9594116a2da839ed1aa346d";
const char* username="l847ulqkmdsv3vx3";
const char* passwd="H0oBbZwHmj";
const char* Url="gz-3-mqtt.iot-api.com";
const char* pubtopic="attributes";
const char* subtopic="attributes/push";
const char* func1="sensor_value";
const char* func2="beep_run";
char* ret;
int esp_Init(void)
{
//	memset(RECS,0,sizeof(RECS));
//	u3_printf("AT+RST\r\n");  //重启
//	delay_ms(2000);
//	
//	memset(RECS,0,sizeof(RECS));
//	u3_printf("ATE0\r\n");    //关闭回显
//	delay_ms(10);
//	if(strcmp(RECS,"OK"))
//		return 1;
	
	u3_printf("AT+CWMODE=3\r\n"); //Station模式
	delay_ms(3000);
	delay_ms(3000);
	if(strcmp(RECS,"OK"))
		return 2;
	
	memset(RECS,0,sizeof(RECS));
	u3_printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
	delay_ms(5000);	delay_ms(3000);
	if(strcmp(RECS,"OK"))
		return 3;
	
	memset(RECS,0,sizeof(RECS));
	u3_printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
	delay_ms(5000); 	delay_ms(3000);
	if(strcmp(RECS,"OK"))
		return 4;
	
	memset(RECS,0,sizeof(RECS));
	u3_printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
	delay_ms(3000); 	delay_ms(3000);
	if(strcmp(RECS,"OK"))
		return 5;
	
	u3_printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
	delay_ms(3000);  	delay_ms(3000);
	if(strcmp(RECS,"OK"))
		return 6;
	memset(RECS,0,sizeof(RECS));
	return 0;
}
//功能：esp发送消息
//参数：无
//返回值：0：发送成功；1：发送失败
char Esp_PUB(void)
{
	memset(RECS,0,sizeof(RECS));
//	u3_printf("AT+MQTTPUB=0,\"%s\",\"\\{\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\}\",0,0\r\n",
//	pubtopic,func1,sensor_value,func2,beep_run,func4,hc501_state,func5,yuzhi);
	//while(RECS[0]);//等待ESP返回数据
//	delay_ms(200);//延时等待数据接收完成 
//	if(strcmp(RECS,"ERROR")==0)
//		return 1;
	return 0;
}
void CommandAnalyse(void)
{

//	if(strncmp(RECS,"+MQTTSUBRECV:",13)==0)
//	{
//			uint8_t i=0;
//		while(RECS[i++] != '\0')             
//		{
//			if(strncmp((RECS+i),func2,8)==0)
//			{
//				while(RECS[i++] != ':');       
//				if(RECS[i]=='1') 
//					 Beep_start;
//				else 
//	      Beep_stop;
//				 	
//				memset(RECS,0,sizeof(RECS));
//			}
//	
//				if(strncmp((RECS+i),func5,5)==0)
//			{
//				while(RECS[i++] != ':');
//				yuzhi=((int)RECS[i]-'0')*10+RECS[i+1]-'0';
//			memset(RECS,0,sizeof(RECS));
//			}
////	
//		}
//		
//		
//		
//	}
}

 void esp8266(void){
//	 	u3_printf("AT+RST\r\n");  //重启
//	delay_ms(2000);

	u3_printf("AT+CWMODE=3\r\n"); //Station模式
	delay_ms(1000);


	

	u3_printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
	delay_ms(2000);

	u3_printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
	delay_ms(3000);


	u3_printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
	delay_ms(2000);

	u3_printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
	delay_ms(500);
 
 }







