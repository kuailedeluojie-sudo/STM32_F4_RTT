/**
  ******************************************************************************
  * @file    bsp_breath_led.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ȫ��LED������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./led/bsp_color_led.h"


 /**
  * @brief  ����TIM3�������PWMʱ�õ���I/O
  * @param  ��
  * @retval ��
  */
static void TIMx_GPIO_Config(void) 
{
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( COLOR_TIM_GPIO_CLK, ENABLE); 

		GPIO_PinAFConfig(COLOR_RED_GPIO_PORT,COLOR_RED_PINSOURCE,COLOR_RED_AF); 
		GPIO_PinAFConfig(COLOR_GREEN_GPIO_PORT,COLOR_GREEN_PINSOURCE,COLOR_GREEN_AF); 
		GPIO_PinAFConfig(COLOR_BLUE_GPIO_PORT,COLOR_BLUE_PINSOURCE,COLOR_BLUE_AF);  
	
		/*COLOR_LED1*/															   
		GPIO_InitStructure.GPIO_Pin = COLOR_RED_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
		GPIO_Init(COLOR_RED_GPIO_PORT, &GPIO_InitStructure);	
    
    /*COLOR_LED2*/															   
		GPIO_InitStructure.GPIO_Pin = COLOR_GREEN_PIN;	
    GPIO_Init(COLOR_GREEN_GPIO_PORT, &GPIO_InitStructure);	
    
    /*COLOR_LED3*/															   
		GPIO_InitStructure.GPIO_Pin = COLOR_BLUE_PIN;	
    GPIO_Init(COLOR_BLUE_GPIO_PORT, &GPIO_InitStructure);	
		
}



/**
  * @brief  ����COLOR_TIMx�����PWM�źŵ�ģʽ�������ڡ�����
  * @param  ��
  * @retval ��
  */
static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;


	// ����TIMx_CLK,x[2,3,4,5] 
  COLOR_TIM_APBxClock_FUN(COLOR_TIM_CLK, ENABLE); 
	
  /* �ۼ� TIM_Period�������һ�����»����ж�*/		 
  TIM_TimeBaseStructure.TIM_Period = 256-1;       //����ʱ����0������255����Ϊ256�Σ�Ϊһ����ʱ����
	
	//��ʱ��ʱ��ԴTIMxCLK = 2 * PCLK1  
  //				PCLK1 = HCLK / 4 
  //				=> TIMxCLK = HCLK / 2 = SystemCoreClock /2
	// ��ʱ��Ƶ��Ϊ = TIMxCLK/(TIM_Prescaler+1) = (SystemCoreClock /2)/((SystemCoreClock/2)/1000000)*30 = 1000000/30 = 1/30MHz
  
	/*������ʱ������TIM_Prescaler����Ч�������ü��ɣ��ж�����С ����˸�죬������˸����*/
	TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)*30-1;	    
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;		 //����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  	
	// ��ʼ����ʱ��TIMx, x[2,3,4,5]
	TIM_TimeBaseInit(COLOR_TIM, &TIM_TimeBaseStructure);	
	
	
	/*PWMģʽ����*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
  TIM_OCInitStructure.TIM_Pulse = 0;	  														//���ó�ʼPWM������Ϊ0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  	  //����ʱ������ֵС��CCR_ValʱΪ�͵�ƽ LED����
 
  //ʹ��ͨ��  
  COLOR_RED_TIM_OCxInit(COLOR_TIM, &TIM_OCInitStructure);	 							
	/*ʹ��ͨ������*/
	COLOR_RED_TIM_OCxPreloadConfig(COLOR_TIM, TIM_OCPreload_Enable);
	
	//ʹ��ͨ��  
	COLOR_GREEN_TIM_OCxInit(COLOR_TIM, &TIM_OCInitStructure);	 
	/*ʹ��ͨ������*/
	COLOR_GREEN_TIM_OCxPreloadConfig(COLOR_TIM, TIM_OCPreload_Enable);

  //ʹ��ͨ��  
  COLOR_BLUE_TIM_OCxInit(COLOR_TIM, &TIM_OCInitStructure);	 
	/*ʹ��ͨ������*/
	COLOR_BLUE_TIM_OCxPreloadConfig(COLOR_TIM, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(COLOR_TIM, ENABLE);			//ʹ��TIM���ؼĴ���ARR
	
	// ʹ�ܼ�����
	TIM_Cmd(COLOR_TIM, ENABLE);																		


}


 /**
  * @brief  ����RGB LED����ɫ
	* @param  rgb:Ҫ����LED��ʾ����ɫֵ��ʽRGB888
  * @retval ��
  */
void SetRGBColor(uint32_t rgb)
{
	//������ɫֵ�޸Ķ�ʱ���ıȽϼĴ���ֵ
	COLOR_TIM->COLOR_RED_CCRx = (uint8_t)(rgb>>16);			//R
	COLOR_TIM->COLOR_GREEN_CCRx = (uint8_t)(rgb>>8);	  //G     
	COLOR_TIM->COLOR_BLUE_CCRx = (uint8_t)rgb;						//B
}

 /**
  * @brief  ����RGB LED����ɫ
	* @param  r\g\b:Ҫ����LED��ʾ����ɫֵ
  * @retval ��
  */
void SetColorValue(uint8_t r,uint8_t g,uint8_t b)
{
	//������ɫֵ�޸Ķ�ʱ���ıȽϼĴ���ֵ
	COLOR_TIM->COLOR_RED_CCRx = r;	
	COLOR_TIM->COLOR_GREEN_CCRx = g;	  
	COLOR_TIM->COLOR_BLUE_CCRx = b;	
}


/**
  * @brief  ��ʼ��������
  * @param  ��
  * @retval ��
  */
void ColorLED_Config(void)
{

	TIMx_GPIO_Config();
	
	TIM_Mode_Config();
	
	//�ϵ��Ĭ����ʾ
	SetColorValue(0xff,0xff,0xff);

}

/*********************************************END OF FILE**********************/
