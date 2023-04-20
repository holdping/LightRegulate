#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
 
	    
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
    HC501.GPIO_Mode	         =  GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&HC501);
}