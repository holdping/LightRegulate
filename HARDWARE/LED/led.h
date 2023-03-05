#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"
#include "sys.h"
 

#define LED0  PAout(3)  // led灯 
#define HOT   PAout(4)  // 制热片
#define COLD  PAout(7)  // 制冷片
#define FANS  PAout(11) // 风扇
#define SMOKE PAout(8)  // 加湿器


#define LED3 PAout(12)// PA12

void LED_Init(void);
#endif
