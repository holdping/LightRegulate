#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "Timer.h" 
	    
//LED IO��ʼ��
void LED_Init(void)
{
 
						GPIO_InitTypeDef  GPIO_InitStructure;
							
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA�˿�ʱ��
						
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;				 //LED0-->PC.13 �˿�����
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_Init(GPIOB, &GPIO_InitStructure);
						GPIO_ResetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_8);						 //���̵�������ȫ������
}

void KEY_init(void)
{
    GPIO_InitTypeDef KEY;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    KEY.GPIO_Pin           =  GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
    KEY.GPIO_Speed         =  GPIO_Speed_50MHz;
    KEY.GPIO_Mode	       =  GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&KEY);

		GPIO_InitTypeDef HC501;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		HC501.GPIO_Pin           =  GPIO_Pin_3;
		HC501.GPIO_Speed         =  GPIO_Speed_50MHz;
		HC501.GPIO_Mode	         =  GPIO_Mode_IPD;
		GPIO_Init(GPIOB,&HC501);
}  
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
    //按键端口初始化
    KEY_init();	 
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //使能复用功能时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	
 
    //GPIOA5 中断线以及中断初始化配置   下降沿触发
    //选择EXTI信号源
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5|GPIO_PinSource6);
    //确定中断线、中断模式、触发方式并使能：
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5|EXTI_Line6;	//KEY3,KEY4
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);
		 GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3); 
    //确定中断线、中断模式、触发方式并使能：
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		    //确定中断源、优先级（抢占优先级和子优先级），使能：
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
    //确定中断源、优先级（抢占优先级和子优先级），使能：
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}

u8 dust=0;
void EXTI9_5_IRQHandler()
{
		delay_ms(10);//消抖
		if(KEY3==0)	  //按键KEY3
			{
				dust += 25;
				TIM_SetCompare2(TIM3,dust);
			}
		else if (KEY4==0)
			{
				dust -= 25;
				TIM_SetCompare2(TIM3,dust);
			}
			
		EXTI_ClearITPendingBit(EXTI_Line5|EXTI_Line6);  //清除LINE5,6上的中断标志位  
}

void EXTI3_IRQHandler()
{
		
		if(HC501s==0)	  //按键KEY3
			{
				TIM_Cmd(TIM2,ENABLE);
				dust=0;
				TIM_SetCompare2(TIM3,dust);
			}

			
		EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE5,6上的中断标志位  
}

