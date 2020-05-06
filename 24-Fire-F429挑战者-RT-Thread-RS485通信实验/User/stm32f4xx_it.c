/* 该文件统一用于存放中断服务函数 */
/* RT-Thread相关头文件 */
#include <rthw.h>
#include <rtthread.h>

#include "stm32f4xx.h"
#include "./485/bsp_485.h"

void _485_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();

  bsp_485_IRQHandler();

  /* 离开中断 */
  rt_interrupt_leave();

}

