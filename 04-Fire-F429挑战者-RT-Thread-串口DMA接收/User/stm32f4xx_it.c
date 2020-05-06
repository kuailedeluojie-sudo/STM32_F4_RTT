/* 该文件统一用于存放中断服务函数 */
#include "stm32f4xx.h"

#include "board.h"
#include "rtthread.h"


// 串口中断服务函数
void DEBUG_USART_IRQHandler(void)
{
	if(USART_GetITStatus(DEBUG_USART,USART_IT_IDLE)!=RESET)
	{		
      Uart_DMA_Rx_Data();       /* 释放一个信号量，表示数据已接收 */
      USART_ReceiveData(DEBUG_USART); /* 清除标志位 */
	}	 
}
