#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"
#include "sys.h"
 

#define LED0  PAout(3)  // led�� 
#define HOT   PAout(4)  // ����Ƭ
#define COLD  PAout(7)  // ����Ƭ
#define FANS  PAout(11) // ����
#define SMOKE PAout(8)  // ��ʪ��


#define LED3 PAout(12)// PA12

void LED_Init(void);
#endif
