/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./tim/bsp_basic_tim.h"
void  BASIC_TIM_IRQHandler (void)
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) 
	{	
		LED1_TOGGLE;
		TIM_ClearITPendingBit(BASIC_TIM , TIM_IT_Update);  		 
	}		 	
}

