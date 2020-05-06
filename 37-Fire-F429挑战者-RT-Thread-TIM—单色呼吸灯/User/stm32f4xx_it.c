/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f4xx.h"
#include "./led/bsp_breath_led.h"

extern uint16_t indexWave[];
	
void  BRE_TIM_IRQHandler (void)
{
	static uint16_t pwm_index = 0;			//����PWM���
	static uint16_t period_cnt = 0;		//���ڼ���������
	
	if (TIM_GetITStatus(BRE_TIM, TIM_IT_Update) != RESET)	//TIM_IT_Update
 	{			
			period_cnt++;
			
			BRE_TIM->BRE_LED_CCRx = indexWave[pwm_index];	//����PWM���޸Ķ�ʱ���ıȽϼĴ���ֵ

			//ÿ��PWM���е�ÿ��Ԫ��ʹ��period_class��
			if(period_cnt > period_class)				 				
			{				

				pwm_index++;												//��־PWM��ָ����һ��Ԫ��
				

				//��PWM���ѵ����β������ָ���ͷ
				if( pwm_index >=  POINT_NUM)			
				{
					pwm_index=0;								
				}
				
				period_cnt=0;											//�������ڼ�����־
			}	
			else
			{
			}	
		
		TIM_ClearITPendingBit (BRE_TIM, TIM_IT_Update);	//����Ҫ����жϱ�־λ
	}
}
