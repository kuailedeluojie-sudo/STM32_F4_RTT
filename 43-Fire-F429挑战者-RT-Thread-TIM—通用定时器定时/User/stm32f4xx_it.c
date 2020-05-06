/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f4xx.h"

#include "./led/bsp_led.h"
#include "./tim/bsp_general_tim.h"

void  GENERAL_TIM_IRQHandler (void)
{
	if ( TIM_GetITStatus( GENERAL_TIM, TIM_IT_Update) != RESET ) 
	{	
		LED1_TOGGLE;
		TIM_ClearITPendingBit(GENERAL_TIM , TIM_IT_Update);  		 
	}		 	
}


