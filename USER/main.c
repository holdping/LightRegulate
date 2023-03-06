#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "string.h"
//#include "bsp_adc.h"
#include <stdio.h>
#include "esp.h"
#include "usart3.h"
#include "OLED.h"
#include "sys.h"
#include "adc.h"
#include "dht11.h"
  extern u16 co2_value;
	extern u8 soil_value;
	extern u16 light_value;
	extern char RECS[600];
	extern char RECS1[600];
extern u8 DHT11_Temp,DHT11_Hum;		
int main(void)
	
{  
	  LED_Init();
		usart1_init(115200);
		usart3_init(115200);
	 soil_value= get_adc_value(1);
	while(1)
	{ 
      DHT11_Read_Data(&DHT11_Temp,&DHT11_Hum);	//获取空气温湿度
		u1_printf("co0 \r\n");
//		memset(RECS,0,sizeof(RECS));
//		COLD=1;
		delay_ms(1000);
		delay_ms(1000);
//		u3_printf("test usart3:%s\r\n",RECS1);
//		memset(RECS1,0,sizeof(RECS1));
//		COLD=0;
//		delay_ms(1000);
//		delay_ms(1000);

	}
}
void loop(void)
{
	while(1)
	{
		//判断温湿度阈值
		DHT11_Read_Data(&DHT11_Temp,&DHT11_Hum);
		if(DHT11_Temp<25)
			{
		    HOT=0;COLD=1;
			}
			else if(DHT11_Temp>30)
			{
							
		    HOT=1;COLD=0;
			}
		//判断土壤湿度
			soil_value=get_adc_value(3);
          if(soil_value<10)
			{
		    jsq=0;
			}
			else if(soil_value>30)
			{
							
		    jsq=1;
			}
       //判断光照
			light_value=get_adc_value(2);
          if(light_value<70)
			{
		    LED0=0;
			}
			else if(light_value>90)
			{
							
		    LED0=1;
			}			
			
			
			//判断二氧化碳
			co2_value= get_adc_value(1);
          if(co2_value<70)
			{
		    FANS=0;
			}
			else if(co2_value>90)
			{
							
		    FANS=1;
			}			
						
	}
}
