#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#define LED3 PBout(5)
void TIM3_PWM_Init(uint16_t TIM3_Prescaler, uint16_t TIM_Period, uint16_t CCR_A); 
void Timer2_Init(void);
#endif