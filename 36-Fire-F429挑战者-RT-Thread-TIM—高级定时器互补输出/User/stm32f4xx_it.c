/* 该文件统一用于存放中断服务函数 */
#include "stm32f4xx.h"
#include "board.h" 


void  ADVANCE_TIM_IRQHandler (void)
{
	if ( TIM_GetITStatus( ADVANCE_TIM, TIM_IT_Update) != RESET ) 
	{	
		LED1_TOGGLE;
		TIM_ClearITPendingBit(ADVANCE_TIM , TIM_IT_Update);  		 
	}		 	
}


