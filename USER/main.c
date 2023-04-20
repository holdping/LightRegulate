#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "string.h"
#include <stdio.h>
#include "usart3.h"
#include "sys.h"
#include "adc.h"
#include "Timer.h"
uint8_t Key_GetNum(void);
void KEY_ui(void);
void LightRegulate(void);

int main(void)
	
{  
	  u8 light = 0;
	  LED_Init();
	  KEY_init();
	  ADC_Init();
	  TIM3_PWM_Init(7200,10000);
  	  usart3_init(115200);

	while(1)
	{ 
		
		light 	= ADC_Trans(ADC_Channel_1,10);
	   	u3_printf("light:%d\r\n",light);
		if(HC501s)
			LED3=1;
		KEY_ui();

	}
}

uint8_t Key_GetNum(void)
{
    uint8_t KeyNum = 0;
    if (KEY1==0) //KEY 可能被按下
    {
        Delay_ms(20);//消抖
		 if (KEY1==0)//判断KEY是否真的按下
        while (KEY1 == 0);//等待按键释放
        Delay_ms(20);
        KeyNum = 1;
    }
    if (KEY2 == 0)
    {
        Delay_ms(20);
		if (KEY2 == 0)
        while (KEY2 == 0);
        Delay_ms(20);
        KeyNum = 2;
    }
    
	    if (KEY3==0)
    {
        Delay_ms(20);
		if (KEY3==0)
        while (KEY3 == 0);
        Delay_ms(20);
        KeyNum = 3;
    }
    if (KEY4 == 0)
    {
        Delay_ms(20);
		if (KEY4 == 0)
        while (KEY4 == 0);
        Delay_ms(20);
        KeyNum = 4;
    }
    
    return KeyNum;
}

void KEY_ui(void)
{
	u8 KEY_NUm = Key_GetNum();
	switch (KEY_NUm)
	{
	case 1:
				LightRegulate();
				LED2 = 0 ; 
				break;
	case 2:
		LED2 = 1 ; 
				switch (KEY_NUm)
				{

			case 3:

				break;
			case 4:

				break;
			default:
				break;		
				}
				break;
	default:
		break;
	}
}
void LightRegulate(void)
{

	if ((ligh>75) && (light<=100))
		TIM_SetCompare2(TIM3,100);
	else if((ligh>50) && (light<=75))
	TIM_SetCompare2(TIM3,75);
	else if ((ligh>25) && (light<=50))
	TIM_SetCompare2(TIM3,50);
	else if ((ligh=>0) && (light<=25))
	TIM_SetCompare2(TIM3,25);
}