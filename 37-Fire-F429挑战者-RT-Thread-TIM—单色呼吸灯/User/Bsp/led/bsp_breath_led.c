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
__IO uint16_t period_class = 10;

/* LED���ȵȼ� PWM��,ָ������ ���˱�ʹ�ù���Ŀ¼�µ�python�ű�index_wave.py����*/
uint16_t indexWave[] = {
1, 1, 1, 1, 2, 2, 2, 2, 3, 3,
4, 4, 5, 5, 6, 7, 8, 9, 10, 
11, 13, 15, 17, 19, 22, 25,
28, 32, 36, 41, 47, 53, 61,
69, 79, 89, 102, 116, 131, 
149, 170, 193, 219, 250, 284,
323, 367, 417, 474, 539, 613, 
697, 792, 901, 1024, 1024, 901, 
792, 697, 613, 539, 474, 417, 
367, 323, 284, 250, 219, 193, 
170, 149, 131, 116, 102, 89, 79,
69, 61, 53, 47, 41, 36, 32, 28, 
25, 22, 19, 17, 15, 13, 11, 10, 
9, 8, 7, 6, 5, 5, 4, 4, 3, 3, 2,
2, 2, 2, 1, 1, 1, 1	
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
		RCC_AHB1PeriphClockCmd ( BRE_LED_GPIO_CLK, ENABLE); 

		GPIO_PinAFConfig(BRE_LED_GPIO_PORT,BRE_LED_PINSOURCE,BRE_LED_AF); 
	
		/*BREATH_LED1*/															   
		GPIO_InitStructure.GPIO_Pin = BRE_LED_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
		GPIO_Init(BRE_LED_GPIO_PORT, &GPIO_InitStructure);	    
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
	
	//Ҫ��
	//TIM_Period����PWM������ֵ��Χһ��
	//TIM_Prescaler��ԽСԽ�ã��ɼ�����˸����
	//PERIOD_CLASS���жϷ������п��Ƶ�����ѭ���Ĵ������������ɿ���������ߵ�����
	//POINT_NUM��PWM���Ԫ�أ�����PWM������ߵĲ�������

	/*************��ʵ���е�����***************/	
	/***********************************************
		#PWM����
		POINT_NUM = 110

		#���ڱ���
		PERIOD_CLASS = 10

		#��ʱ����ʱ����
		TIMER_TIM_Period = 2**10
		#��ʱ����Ƶ
		TIMER_TIM_Prescaler = 250

		#STM32ϵͳʱ��Ƶ�ʺ�����
		f_hclk = 180000000

		#��ʱ����ʱƵ��
		f_pclk1 = f_hclk/2
		t_pclk1 = 1/f_pclk1

		#��ʱ��update�¼�����
		t_timer = t_pclk1*TIMER_TIM_Prescaler*TIMER_TIM_Period

		#ÿ��PWM���ʱ��
		T_Point = t_timer * PERIOD_CLASS 

		#������������
		T_Up_Down_Cycle = T_Point * POINT_NUM

		print ("�������ڣ�",T_Up_Down_Cycle)
		
	#���н����
	
	�������ڣ�3.12888
	************************************************************/	
	
  TIM_TimeBaseStructure.TIM_Period = (1024-1);      					//����ʱ����0������ TIM_Period+1 ��Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = (250-1);	    			//����Ԥ��Ƶ
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
  
	BRE_TIM_OCxInit(BRE_TIM, &TIM_OCInitStructure);	 //ʹ��ͨ��
  
	/*ʹ��ͨ������*/
	BRE_TIM_OCxPreloadConfig(BRE_TIM, TIM_OCPreload_Enable);
	
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
