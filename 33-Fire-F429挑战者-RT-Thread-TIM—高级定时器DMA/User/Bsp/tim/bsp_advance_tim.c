/**
  ******************************************************************************
  * @file    bsp_advance_tim.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   �߼����ƶ�ʱ��DMA�����������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./tim/bsp_advance_tim.h"


uint16_t aSRC_Buffer[TIM_DMA_BUFSIZE] ={383, 767, 127};

/**
  * @brief  ����TIM�������PWMʱ�õ���I/O
  * @param  ��
  * @retval ��
  */
static void TIMx_GPIO_Config(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
	
	/*������ʱ����ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (ADVANCE_OCPWM_GPIO_CLK , ENABLE); 
  /* ָ�����Ÿ��ù��� */
	GPIO_PinAFConfig(ADVANCE_OCPWM_GPIO_PORT,ADVANCE_OCPWM_PINSOURCE, ADVANCE_OCPWM_AF); 
	
	/* ��ʱ���������ų�ʼ�� */															   
	GPIO_InitStructure.GPIO_Pin = ADVANCE_OCPWM_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(ADVANCE_OCPWM_GPIO_PORT, &GPIO_InitStructure);
	
	/* DMA clock enable */
  RCC_AHB1PeriphClockCmd(TIM_DMA_CLK , ENABLE);	
	
	DMA_DeInit(TIM_DMA_STREAM);
	/* ȷ��DMA��������λ��� */
  while (DMA_GetCmdStatus(TIM_DMA_STREAM) != DISABLE)  {
  }
	
  DMA_InitStructure.DMA_Channel = TIM_DMA_CHANNEL;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(TIM_DMA_ADDRESS) ;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aSRC_Buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = TIM_DMA_BUFSIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  DMA_Init(TIM_DMA_STREAM, &DMA_InitStructure);
}

/*
 * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
 * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
 * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
 *-----------------------------------------------------------------------------
 * TIM_Prescaler         ����
 * TIM_CounterMode			 TIMx,x[6,7]û�У��������У�������ʱ����
 * TIM_Period            ����
 * TIM_ClockDivision     TIMx,x[6,7]û�У���������(������ʱ��)
 * TIM_RepetitionCounter TIMx,x[1,8]����(�߼���ʱ��)
 *-----------------------------------------------------------------------------
 */
static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// ����TIMx_CLK,x[1,8] 
  RCC_APB2PeriphClockCmd(ADVANCE_TIM_CLK, ENABLE); 

  /* �ۼ� TIM_Period�������һ�����»����ж�*/		
  //����ʱ����0������1023����Ϊ1024�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Period = 1024-1;
	// �߼����ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK=180MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100000Hz
  TIM_TimeBaseStructure.TIM_Prescaler = 18000-1;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  // �ظ�������
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��TIMx, x[1,8]
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);
	
  /*PWMģʽ����*/
	//����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 383;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  //ʹ��ͨ��1
  TIM_OC1Init(ADVANCE_TIM, &TIM_OCInitStructure);
		
	/* Enable preload feature */
  TIM_OC1PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);
	
	// ʹ�ܶ�ʱ��
	TIM_Cmd(ADVANCE_TIM, ENABLE);	
	
	/* DMA enable*/
  DMA_Cmd(TIM_DMA_STREAM, ENABLE);
	
	/* �ȴ�DMA��������Ч*/
  while(DMA_GetCmdStatus(TIM_DMA_STREAM) != ENABLE)
  {
	}		
	/* TIM Update DMA Request enable */
  TIM_DMACmd(ADVANCE_TIM, TIM_DMA_CC1, ENABLE);	

	/* �������ʹ�� */
  TIM_CtrlPWMOutputs(ADVANCE_TIM, ENABLE);
}

/**
  * @brief  ��ʼ���߼����ƶ�ʱ��
  * @param  ��
  * @retval ��
  */
void TIMx_Configuration(void)
{  
	TIMx_GPIO_Config();
	
  TIM_Mode_Config();
}

/*********************************************END OF FILE**********************/
