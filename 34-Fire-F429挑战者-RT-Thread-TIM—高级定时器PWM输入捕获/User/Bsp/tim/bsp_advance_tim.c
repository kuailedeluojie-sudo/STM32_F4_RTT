/**
  ******************************************************************************
  * @file    bsp_advance_tim.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ͨ�ö�ʱ����ʱ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./tim/bsp_advance_tim.h"

/**
  * @brief  ����TIM�������PWMʱ�õ���I/O
  * @param  ��
  * @retval ��
  */
static void TIMx_GPIO_Config(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����LED��ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (GENERAL_OCPWM_GPIO_CLK, ENABLE); 
	RCC_AHB1PeriphClockCmd (ADVANCE_ICPWM_GPIO_CLK, ENABLE); 	

	/* ��ʱ���������� */
	GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT,GENERAL_OCPWM_PINSOURCE,GENERAL_OCPWM_AF); 
	GPIO_PinAFConfig(ADVANCE_ICPWM_GPIO_PORT,ADVANCE_ICPWM_PINSOURCE,ADVANCE_ICPWM_AF); 
	
	/* ͨ�ö�ʱ��PWM������� */															   
	GPIO_InitStructure.GPIO_Pin = GENERAL_OCPWM_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GENERAL_OCPWM_GPIO_PORT, &GPIO_InitStructure);
	
	/* �߼����ƶ�ʱ��PWM���벶������ */
	GPIO_InitStructure.GPIO_Pin = ADVANCE_ICPWM_PIN;	
	GPIO_Init(ADVANCE_ICPWM_GPIO_PORT, &GPIO_InitStructure);
}

 /**
  * @brief  �߼����ƶ�ʱ�� TIMx,x[1,8]�ж����ȼ�����
  * @param  ��
  * @retval ��
  */
static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQn; 	
		// ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ���������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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
static void TIM_PWMOUTPUT_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// ����TIMx_CLK,x[2,3,4,5,12,13,14] 
  RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK, ENABLE); 

  /* �ۼ� TIM_Period�������һ�����»����ж�*/		
  //����ʱ����0������9999����Ϊ10000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Period = 10000-1;       
	
	// ͨ�ö�ʱ��2ʱ��ԴTIMxCLK = HCLK/2=90MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = 900-1;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// ��ʼ����ʱ��TIMx, x[1,8]
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	/* PWM���ģʽ���� */
	/* ����ΪPWMģʽ1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	/* PWM������ */
  TIM_OCInitStructure.TIM_Pulse = 3000-1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/* ʹ��ͨ��1 */
  TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);	
	/*ʹ��ͨ��1����*/
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	// ʹ�ܶ�ʱ��
	TIM_Cmd(GENERAL_TIM, ENABLE);	
}

static void TIM_PWMINPUT_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	// ����TIMx_CLK,x[1,8] 
  RCC_APB2PeriphClockCmd(ADVANCE_TIM_CLK, ENABLE); 

  TIM_TimeBaseStructure.TIM_Period = 0xFFFF-1; 	
	// �߼����ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK=180MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
  TIM_TimeBaseStructure.TIM_Prescaler = 1800-1;	
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	
	// ��ʼ����ʱ��TIMx, x[1,8]
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);
	
	/* IC1���������ش��� TI1FP1 */
  TIM_ICInitStructure.TIM_Channel = ADVANCE_IC1PWM_CHANNEL;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	/* IC2�����½��ش��� TI1FP2 */	
	TIM_ICInitStructure.TIM_Channel = ADVANCE_IC2PWM_CHANNEL;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_PWMIConfig(ADVANCE_TIM, &TIM_ICInitStructure);
	
	/* ѡ��ʱ�����봥��: TI1FP1 */
  TIM_SelectInputTrigger(ADVANCE_TIM, TIM_TS_TI1FP1);		

  /* ѡ���ģʽ: ��λģʽ */
  TIM_SelectSlaveMode(ADVANCE_TIM, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(ADVANCE_TIM,TIM_MasterSlaveMode_Enable);

  /* ʹ�ܸ߼����ƶ�ʱ�� */
  TIM_Cmd(ADVANCE_TIM, ENABLE);

  /* ʹ�ܲ���/�Ƚ�2�ж����� */
  TIM_ITConfig(ADVANCE_TIM, TIM_IT_CC1, ENABLE);
}


/**
  * @brief  ��ʼ���߼����ƶ�ʱ����ʱ��1ms����һ���ж�
  * @param  ��
  * @retval ��
  */
void TIMx_Configuration(void)
{
	TIMx_GPIO_Config();
	
	TIMx_NVIC_Configuration();	
  
  TIM_PWMOUTPUT_Config();
	
	TIM_PWMINPUT_Config();
}

/*********************************************END OF FILE**********************/
