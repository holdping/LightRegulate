#include "delay.h"
#include "usart3.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"
//串口接收缓存区 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 				//发送缓冲,最大USART3_MAX_SEND_LEN字节
u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 				//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
u8 USART1_TX_BUF[USART1_MAX_SEND_LEN]; 				//发送缓冲,最大USART3_MAX_SEND_LEN字节

char 	 RECS[600];
char 	 RECS1[600];
unsigned char i;
unsigned char j;

//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
vu16 USART3_RX_STA = 0;
vu16 USART1_RX_STA = 0;


//串口3接收中断服务函数
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE))
	{ 
		RECS[i++]=USART_ReceiveData(USART3);   		//将数据存入缓冲区
		if((RECS[i-2]=='\r')|(RECS[i-1]=='\n'))    //判断接受到的数据是否为换行结尾 ，是就从倒数第二位结束此数据
		{
			RECS[i-2]='\0';                
			i = 0;
	   
		}else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //检测中断空闲位有没有清除
    {
        USART3->SR;//??SR???
        USART3->DR; //??DR
    }
}
	
}



//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率	  
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //串口3时钟使能

 	USART_DeInit(USART3);  //复位串口3
		 //USART3_TX   
	GPIO_InitStructure.GPIO_Pin 					= GPIO_Pin_10; 		//PB10
	GPIO_InitStructure.GPIO_Speed 					= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode		    		= GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
   
    //USART3_RX	  
	GPIO_InitStructure.GPIO_Pin 			= GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode 			= GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11
	
	USART_InitStructure.USART_BaudRate 				= bound;							//波特率一般设置为115200;
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;				//字长为8位数据格式
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;					//一个停止位
	USART_InitStructure.USART_Parity 				= USART_Parity_No;					//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode 					= USART_Mode_Rx | USART_Mode_Tx;						//收发模式
  
	USART_Init(USART3, &USART_InitStructure); 						//初始化串口	3
	USART_Cmd(USART3, ENABLE);                    					//使能串口 
	
	//使能接收中断
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);					//开启中断   
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel 					= USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 2;			//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		= 3;			//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd 				= ENABLE;		//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);										//根据指定的参数初始化VIC寄存器
	USART3_RX_STA=0;		//清零

}

//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}
