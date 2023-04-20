#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#define LED3 PBout(5)
void pwm_Init(u16 TIM3_Prescaler, u16 TIM_Period);
void Timer2_Init(void);
#endif