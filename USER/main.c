#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "string.h"
#include "bsp_adc.h"
#include <stdio.h>
#include "esp.h"
#include "usart3.h"

	extern char RECS[600];
	extern char RECS1[600];	
int main(void)
	
{  
	  LED_Init();
		usart1_init(115200);
		usart3_init(115200);
	while(1)
	{ 
		u1_printf("sdfsdf%s\r\n",RECS);
		memset(RECS,0,sizeof(RECS));
		COLD=1;
		delay_ms(1000);
		delay_ms(1000);
		u3_printf("test usart3:%s\r\n",RECS1);
		memset(RECS1,0,sizeof(RECS1));
		COLD=0;
		delay_ms(1000);
		delay_ms(1000);

	}
}

