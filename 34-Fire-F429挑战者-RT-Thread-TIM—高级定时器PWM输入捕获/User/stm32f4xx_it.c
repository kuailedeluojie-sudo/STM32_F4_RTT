/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f4xx.h"
#include "./tim/bsp_advance_tim.h"
#include "./uart/bsp_debug_usart.h"

/** @addtogroup STM32F429I_DISCOVERY_Examples
  * @{
  */

/** @addtogroup FMC_SDRAM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t IC2Value = 0;
__IO uint16_t IC1Value = 0;
__IO float DutyCycle = 0;
__IO float Frequency = 0;

void  ADVANCE_TIM_IRQHandler (void)
{
  /* �����ʱ������/�Ƚ�1�ж� */
  TIM_ClearITPendingBit(ADVANCE_TIM, TIM_IT_CC1);

  /* ��ȡ���벶��ֵ */
  IC1Value = TIM_GetCapture1(ADVANCE_TIM);
  IC2Value = TIM_GetCapture2(ADVANCE_TIM);	
  printf("IC1Value = %d  IC2Value = %d ",IC1Value,IC2Value);
	
  if (IC1Value != 0)
  {
    /* ռ�ձȼ��� */
    DutyCycle = (float)(IC2Value * 100) / IC1Value;

    /* Ƶ�ʼ��� */
    Frequency = 180000000/1800/(float)IC1Value;
		printf("ռ�ձȣ�%0.2f%%   Ƶ�ʣ�%0.2fHz\n",DutyCycle,Frequency);
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
  }
}

