/* 该文件统一用于存放中断服务函数 */
#include "stm32f4xx.h"
#include "./led/bsp_breath_led.h"

extern uint16_t indexWave[];
	
void  BRE_TIM_IRQHandler (void)
{
	static uint16_t pwm_index = 0;			//用于PWM查表
	static uint16_t period_cnt = 0;		//用于计算周期数
	
	if (TIM_GetITStatus(BRE_TIM, TIM_IT_Update) != RESET)	//TIM_IT_Update
 	{			
			period_cnt++;
			
			BRE_TIM->BRE_LED_CCRx = indexWave[pwm_index];	//根据PWM表修改定时器的比较寄存器值

			//每个PWM表中的每个元素使用period_class次
			if(period_cnt > period_class)				 				
			{				

				pwm_index++;												//标志PWM表指向下一个元素
				

				//若PWM表已到达结尾，重新指向表头
				if( pwm_index >=  POINT_NUM)			
				{
					pwm_index=0;								
				}
				
				period_cnt=0;											//重置周期计数标志
			}	
			else
			{
			}	
		
		TIM_ClearITPendingBit (BRE_TIM, TIM_IT_Update);	//必须要清除中断标志位
	}
}
