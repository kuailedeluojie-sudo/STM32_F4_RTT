/* 该文件统一用于存放中断服务函数 */
#include "stm32f4xx.h"

#include "./Bsp/usart/bsp_debug_usart.h"
#include "./Bsp/beep/bsp_beep.h"
/* RT-Thread相关头文件 */
#include <rthw.h>
#include <rtthread.h>

// 闹钟中断服务函数
void RTC_Alarm_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();
  
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {    
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
  }
	/* 闹钟时间到，蜂鸣器响 */
	BEEP_ON;	
  /* 离开中断 */
  rt_interrupt_leave();
  
}

