#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"
#include "sys.h"

#define KEY1  PAin(3)      // 
#define KEY2  PAin(4)      //
#define KEY3  PAin(5)      // 
#define KEY4  PAin(6)      // 
#define LED1  PBout(7)      // 
#define LED2  PBout(8)     // 
#define HC501s PBin(3)

void LED_Init(void);
void KEY_init(void);
#endif
