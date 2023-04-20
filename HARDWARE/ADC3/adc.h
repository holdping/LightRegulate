#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
#include "stm32f0xx.h"

void ADC_Init(void);
u16 ADC_Trans(u8 ch,u8 times);

#endif