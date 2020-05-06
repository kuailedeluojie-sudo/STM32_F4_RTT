/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f4xx.h"

#include "./Bsp/usart/bsp_debug_usart.h"
#include "./Bsp/beep/bsp_beep.h"
/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>

// �����жϷ�����
void RTC_Alarm_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();
  
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {    
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
  }
	/* ����ʱ�䵽���������� */
	BEEP_ON;	
  /* �뿪�ж� */
  rt_interrupt_leave();
  
}

