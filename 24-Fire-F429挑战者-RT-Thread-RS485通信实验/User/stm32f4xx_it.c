/* ���ļ�ͳһ���ڴ���жϷ����� */
/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>

#include "stm32f4xx.h"
#include "./485/bsp_485.h"

void _485_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();

  bsp_485_IRQHandler();

  /* �뿪�ж� */
  rt_interrupt_leave();

}

