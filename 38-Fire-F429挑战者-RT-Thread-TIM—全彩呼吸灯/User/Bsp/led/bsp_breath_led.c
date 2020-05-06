/**
  ******************************************************************************
  * @file    bsp_breath_led.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ����������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./led/bsp_breath_led.h"

//����������ε�Ƶ��
__IO uint16_t period_class = 1;

/* LED���ȵȼ� PWM��,ָ������ ���˱�ʹ�ù���Ŀ¼�µ�python�ű�index_wave.py����*/
uint16_t indexWave[] = {
1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
	2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 
	6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 12, 
	12, 13, 14, 15, 17, 18, 19, 20, 22, 
	23, 25, 27, 29, 31, 33, 36, 38, 41, 
	44, 47, 51, 54, 58, 63, 67, 72, 77, 
	83, 89, 95, 102, 110, 117, 126, 135,
	145, 156, 167, 179, 192, 206, 221, 237, 
	254, 272, 292, 313, 336, 361, 387, 415, 
	445, 477, 512, 512, 477, 445, 415, 387, 
	361, 336, 313, 292, 272, 254, 237, 221, 
	206, 192, 179, 167, 156, 145, 135, 126, 
	117, 110, 102, 95, 89, 83, 77, 72, 67, 63,
	58, 54, 51, 47, 44, 41, 38, 36, 33, 31, 29,
	27, 25, 23, 22, 20, 19, 18, 17, 15, 14, 13,
	12, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5,
	5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2,
	2, 2, 1, 1, 1, 1, 1, 1
};

//����PWM���ж��ٸ�Ԫ��
uint16_t POINT_NUM = sizeof(indexWave)/sizeof(indexWave[0]); 

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
		RCC_AHB1PeriphClockCmd ( BRE_TIM_GPIO_CLK, ENABLE); 

		GPIO_PinAFConfig(BRE_RED_GPIO_PORT,BRE_RED_PINSOURCE,BRE_RED_AF); 
		GPIO_PinAFConfig(BRE_GREEN_GPIO_PORT,BRE_GREEN_PINSOURCE,BRE_GREEN_AF); 
		GPIO_PinAFConfig(BRE_BLUE_GPIO_PORT,BRE_BLUE_PINSOURCE,BRE_BLUE_AF); 

		/* ����LED���õ������� */
		//��
		GPIO_InitStructure.GPIO_Pin = BRE_RED_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
		GPIO_Init(BRE_RED_GPIO_PORT, &GPIO_InitStructure);	    
		
		//��
		GPIO_InitStructure.GPIO_Pin = BRE_GREEN_PIN;	
		GPIO_Init(BRE_GREEN_GPIO_PORT, &GPIO_InitStructure);	 
		
		//��
		GPIO_InitStructure.GPIO_Pin = BRE_BLUE_PIN;	
		GPIO_Init(BRE_BLUE_GPIO_PORT, &GPIO_InitStructure);	 
}


 /**
  * @brief  ͨ�ö�ʱ�� TIMx,x[2,3,4,5]�ж����ȼ�����
  * @param  ��
  * @retval ��
  */ 
static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = BRE_TIM_IRQn; 
	
		// ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	 
	  // ���������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



/**
  * @brief  ����TIM�����PWM�źŵ�ģʽ�������ڡ�����
  * @param  ��
  * @retval ��
  */

static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	// ����TIMx_CLK,x[2,3,4,5] 
  BRE_TIM_APBxClock_FUN(BRE_TIM_CLK, ENABLE); 
	
	/* ������ʱ������ ,���PWM��������жϷ������е�period_cntѭ����������*/	
	
	/* ����ʹ��������������Ϊ3�����Ҽ��ɴﵽ�ܺõ�Ч�� */	
	
	/* ����ʹ��������������Ϊ3�����Ҽ��ɴﵽ�ܺõ�Ч�� */	
	
	//Ҫ��
	//TIM_Period����PWM������ֵ��Χһ��
	//TIM_Prescaler��ԽСԽ�ã��ɼ�����˸����
	//PERIOD_CLASS���жϷ������п��Ƶ�����ѭ���Ĵ������������ɿ���������ߵ�����

	//AMPLITUDE_CLASS���жϷ������п��Ƶ�����ѭ���Ĵ������������ɿ��Ʒ�ֵ��
	//						�ڱ�ʵ������ΪLEDͨ��������ֵ����256���ȼ�����ӦRGB888��ʽ��ͨ������ɫ�ȼ�
	//POINT_NUM��PWM���Ԫ�أ�����PWM������ߵĲ�������

	/*************��ʵ���е�����***************/	
	/***********************************************
		#PWM����
		POINT_NUM = 180

		#���ڱ���
		PERIOD_CLASS = 1

		#��ֵ�ȼ�
		AMPLITUDE_CLASS = 256

		#��ʱ����ʱ����
		TIMER_TIM_Period = 2**9
		#��ʱ����Ƶ
		TIMER_TIM_Prescaler = 12

		#STM32ϵͳʱ��Ƶ�ʺ�����
		f_hclk = 180000000

		#��ʱ����ʱƵ��
		f_pclk1 = f_hclk/2
		t_pclk1 = 1/f_pclk1

		#��ʱ��update�¼�����
		t_timer = t_pclk1*TIMER_TIM_Prescaler*TIMER_TIM_Period

		#ÿ��PWM���ʱ��
		T_Point = t_timer * PERIOD_CLASS * AMPLITUDE_CLASS

		#������������
		T_Up_Down_Cycle = T_Point * POINT_NUM

		print ("�������ڣ�",T_Up_Down_Cycle)

		
	#���н����
	
	�������ڣ�3.145728
	************************************************************/	
	
  TIM_TimeBaseStructure.TIM_Period = (512-1);      					//����ʱ����0������ TIM_Period+1 ��Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = (12-1);	    			//����Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  	
	// ��ʼ����ʱ��TIMx, x[2,3,4,5]
	TIM_TimeBaseInit(BRE_TIM, &TIM_TimeBaseStructure);	
	
	
	/*PWMģʽ����*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
  TIM_OCInitStructure.TIM_Pulse = 0;	  												//���ó�ʼPWM������Ϊ0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ LED����
  
	//ʹ��ͨ��
	BRE_RED_TIM_OCxInit(BRE_TIM, &TIM_OCInitStructure);	 
  /*ʹ��ͨ������*/
	BRE_RED_TIM_OCxPreloadConfig(BRE_TIM, TIM_OCPreload_Enable);
	
	//ʹ��ͨ��
	BRE_GREEN_TIM_OCxInit(BRE_TIM, &TIM_OCInitStructure);	 
  /*ʹ��ͨ������*/
	BRE_GREEN_TIM_OCxPreloadConfig(BRE_TIM, TIM_OCPreload_Enable);


	//ʹ��ͨ��
	BRE_BLUE_TIM_OCxInit(BRE_TIM, &TIM_OCInitStructure);	 
  /*ʹ��ͨ������*/
	BRE_BLUE_TIM_OCxPreloadConfig(BRE_TIM, TIM_OCPreload_Enable);

	
	TIM_ARRPreloadConfig(BRE_TIM, ENABLE);			//ʹ��TIM���ؼĴ���ARR

	// �����������ж�
	TIM_ITConfig(BRE_TIM,TIM_IT_Update,ENABLE);
	
	// ʹ�ܼ�����
	TIM_Cmd(BRE_TIM, ENABLE);	
}

/**
  * @brief  ��ʼ��������
  * @param  ��
  * @retval ��
  */
void BreathLED_Config(void)
{

	TIMx_GPIO_Config();
	
	TIM_Mode_Config();

	TIMx_NVIC_Configuration();	
}

/*********************************************END OF FILE**********************/
