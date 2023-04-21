/**
 * *****************************************************************************
 * @file 	main.c
 * @author 	HXP
 * @date 	2023.4.21
 * @version v1.0
 * @brief   根据光线强度改变LED灯的亮度，红外传感器识别有无人经过，有则开灯，无则关灯
 * *****************************************************************************
*/

#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "string.h"
#include <stdio.h>
#include "usart3.h"
#include "sys.h"
#include "adc.h"
#include "Timer.h"
#include "iwdg.h"
uint8_t Key_GetNum(void);
void 	KEY_ui(void);
void 	LightRegulate(void);
u8 		light = 0;
int main(void)
	
{  

			LED_Init();
			KEY_init();
			ADC1_Init();
			pwm_Init(720,100);
			Timer2_Init();
			IWDG_Init(5,625);
			usart3_init(115200);
			u3_printf("初始化完成%d\r\n");

				while(1)
				{ 
					
					light 	= ADC_Trans(ADC_Channel_1,10);
				u3_printf("light:%d\r\n",light);
					if(HC501s)
					TIM_SetCompare2(TIM3,100);
					KEY_ui();

				}
}

uint8_t Key_GetNum(void)
{
				uint8_t KeyNum = 0;
				if (KEY1==0) //KEY 可能被按下
				{
						delay_ms(20);//消抖
						if (KEY1==0)//判断KEY是否真的按下
						while (KEY1 == 0);//等待按键释放
						delay_ms(20);
						KeyNum = 1;
				}
				if (KEY2 == 0)
				{
						delay_ms(20);
						if (KEY2 == 0)
						while (KEY2 == 0);
						delay_ms(20);
						KeyNum = 2;
				}
				
					if (KEY3==0)
				{
						delay_ms(20);
						if (KEY3==0)
						while (KEY3 == 0);
						delay_ms(20);
						KeyNum = 3;
				}
				if (KEY4 == 0)
				{
						delay_ms(20);
						if (KEY4 == 0)
						while (KEY4 == 0);
						delay_ms(20);
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
						if(HC501s)
						TIM_SetCompare2(TIM3,(dust=100));	
								break;
					default:
								LightRegulate();
						break;
			}
}
void LightRegulate(void)
{

			if ((light>75) && (light<=100))
				dust = 25;
			else if((light>50) && (light<=75))
				dust = 50;
			else if ((light>25) && (light<=50))
				dust = 75;
			else if ((light>=0) && (light<=25))
				dust = 100;
			TIM_SetCompare2(TIM3,dust);
}