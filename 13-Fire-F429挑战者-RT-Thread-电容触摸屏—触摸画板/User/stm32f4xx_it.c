/* 该文件统一用于存放中断服务函数 */
#include "stm32f4xx.h"
#include "board.h" 

/* RT-Thread相关头文件 */
#include <rthw.h>
#include <rtthread.h>

extern void GTP_TouchProcess(void);

void GTP_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();
  
	if(EXTI_GetITStatus(GTP_INT_EXTI_LINE) != RESET) //确保是否产生了EXTI Line中断
	{
		LED2_TOGGLE;
    GTP_TouchProcess();    
		EXTI_ClearITPendingBit(GTP_INT_EXTI_LINE);     //清除中断标志位
	}  
  
  /* 离开中断 */
  rt_interrupt_leave();
  
}


