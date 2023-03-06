#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"
#include "sys.h"
#define LED0_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define HOT_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define COLD_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define FANS_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)
#define jsq_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)

#define LED0  PAout(5)  // led�� 
#define HOT   PAout(4)  // ����Ƭ
#define COLD  PAout(7)  // ����Ƭ
#define FANS  PAout(11) // ����
#define jsq   PAout(8)  // ��ʪ��
#define LED3  PAout(12)// PA12

void LED_Init(void);
#endif
