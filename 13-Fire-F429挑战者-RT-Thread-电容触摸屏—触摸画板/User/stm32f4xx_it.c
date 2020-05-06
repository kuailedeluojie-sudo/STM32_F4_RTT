/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f4xx.h"
#include "board.h" 

/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>

extern void GTP_TouchProcess(void);

void GTP_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();
  
	if(EXTI_GetITStatus(GTP_INT_EXTI_LINE) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		LED2_TOGGLE;
    GTP_TouchProcess();    
		EXTI_ClearITPendingBit(GTP_INT_EXTI_LINE);     //����жϱ�־λ
	}  
  
  /* �뿪�ж� */
  rt_interrupt_leave();
  
}


