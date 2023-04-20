#include "Timer.h"
#include "led.h"

void pwm_Init(u16 TIM3_Prescaler, u16 TIM_Period)
{

	  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); 

  GPIO_InitStructure.GPIO_Pin			 =  GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode		 = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed		 = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);


	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
 /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period 					= TIM_Period-1;
  TIM_TimeBaseStructure.TIM_Prescaler 			= TIM3_Prescaler-1;//系统时钟频率/TIM_Prescaler= 定时器时钟频率    1/定时器时钟频率* TIM_Period = 定时时间
  TIM_TimeBaseStructure.TIM_ClockDivision 	= 0;
  TIM_TimeBaseStructure.TIM_CounterMode 		= TIM_CounterMode_Up;//从0 开始向上计数
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
  /* PWM3 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse 			= 50;
  TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;

  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
 // TIM_ARRPreloadConfig(PWM_TIMx, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);	
}


void Timer2_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period =49999;
	TIM_TimeBaseInitStructure.TIM_Prescaler =7199;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd (TIM2,ENABLE);
	
	
}
u8 cs=0;
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
			
	{	
		{
			TIM_ClearITPendingBit (TIM2,TIM_IT_Update);
			cs++;
			if(cs==2){
						TIM_SetCompare2(TIM3,100);
						cs	 = 0;
						TIM_Cmd(TIM2,DISABLE);
					}

		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
