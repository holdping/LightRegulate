#include "sys.h"
void NVIC_Configuration2(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

}

void SysTick_Init(int n)
{
/**
 * SystemFrequency /1000 1ms ????
 * SystemFrequency / 100000 10us ????
 * SystemFrequency / 1000000 1us ????
 */
if (SysTick_Config(SystemCoreClock/1000000*n)) {
/* Capture error */
	  while(1)
			;
	}
}
