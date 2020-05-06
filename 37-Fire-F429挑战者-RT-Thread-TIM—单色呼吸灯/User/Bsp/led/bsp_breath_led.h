#ifndef __BREATH_LED_H
#define	__BREATH_LED_H

#include "stm32f4xx.h"

/*PWM���еĵ���*/
extern uint16_t  POINT_NUM	;
//����������ε�Ƶ��
extern __IO uint16_t period_class ;


#define RED_LIGHT 		1
#define GREEN_LIGHT 	2
#define BLUE_LIGHT		3

/*Ҫʹ��ʲô��ɫ�ĺ����ƣ���ѡRED_LIGHT��GREEN_LIGHT��BLUE_LIGHT*/
#define LIGHT_COLOR 	RED_LIGHT

/********************��ʱ��ͨ��**************************/
#if  LIGHT_COLOR == RED_LIGHT
	//R ��ɫ��
	#define BRE_TIM           							TIM5
	#define BRE_TIM_CLK       						RCC_APB1Periph_TIM5
	#define BRE_TIM_APBxClock_FUN        RCC_APB1PeriphClockCmd

	#define BRE_TIM_IRQn								TIM5_IRQn
	#define BRE_TIM_IRQHandler 				TIM5_IRQHandler


	#define BRE_LED_PIN                  GPIO_Pin_10                 
	#define BRE_LED_GPIO_PORT            GPIOH                      
	#define BRE_LED_GPIO_CLK             RCC_AHB1Periph_GPIOH
	#define BRE_LED_PINSOURCE							GPIO_PinSource10
	#define BRE_LED_AF										GPIO_AF_TIM5

//ͨ���ȽϼĴ�������TIMx->CCRx��ʽ�ɷ��ʸüĴ����������µıȽ�ֵ������ռ�ձ�
//�Ժ��װ��ʹ��������ʽ��BRE_TIMx->BRE_RED_CCRx ���ɷ��ʸ�ͨ���ıȽϼĴ���
	#define BRE_LED_CCRx									CCR1
	#define BRE_LED_TIM_CHANNEL					TIM_Channel_1

	#define  BRE_TIM_OCxInit              TIM_OC1Init            //ͨ��ѡ��1~4
	#define  BRE_TIM_OCxPreloadConfig    TIM_OC1PreloadConfig 


#elif LIGHT_COLOR == GREEN_LIGHT
	//G ��ɫ��
	#define BRE_TIM           							TIM5
	#define BRE_TIM_CLK       						RCC_APB1Periph_TIM5
	#define BRE_TIM_APBxClock_FUN        RCC_APB1PeriphClockCmd

	#define BRE_TIM_IRQn								TIM5_IRQn
	#define BRE_TIM_IRQHandler 				TIM5_IRQHandler


	#define BRE_LED_PIN                  GPIO_Pin_11                 
	#define BRE_LED_GPIO_PORT            GPIOH                      
	#define BRE_LED_GPIO_CLK             RCC_AHB1Periph_GPIOH
	#define BRE_LED_PINSOURCE							GPIO_PinSource11
	#define BRE_LED_AF										GPIO_AF_TIM5

//ͨ���ȽϼĴ�������TIMx->CCRx��ʽ�ɷ��ʸüĴ����������µıȽ�ֵ������ռ�ձ�
//�Ժ��װ��ʹ��������ʽ��BRE_TIM->BRE_LED_CCRx ���ɷ��ʸ�ͨ���ıȽϼĴ���
	#define BRE_LED_CCRx									CCR2
	#define BRE_LED_TIM_CHANNEL					TIM_Channel_2

	#define  BRE_TIM_OCxInit              TIM_OC2Init            //ͨ��ѡ��1~4
	#define  BRE_TIM_OCxPreloadConfig    TIM_OC2PreloadConfig 

#elif LIGHT_COLOR == BLUE_LIGHT
	//B ��ɫ��
	#define BRE_TIM           							TIM5
	#define BRE_TIM_CLK       						RCC_APB1Periph_TIM5
	#define BRE_TIM_APBxClock_FUN        RCC_APB1PeriphClockCmd

	#define BRE_TIM_IRQn								TIM5_IRQn
	#define BRE_TIM_IRQHandler 				TIM5_IRQHandler


	#define BRE_LED_PIN                  GPIO_Pin_12                 
	#define BRE_LED_GPIO_PORT            GPIOH                      
	#define BRE_LED_GPIO_CLK             RCC_AHB1Periph_GPIOH
	#define BRE_LED_PINSOURCE							GPIO_PinSource12
	#define BRE_LED_AF										GPIO_AF_TIM5

//ͨ���ȽϼĴ�������TIMx->CCRx��ʽ�ɷ��ʸüĴ����������µıȽ�ֵ������ռ�ձ�
//�Ժ��װ��ʹ��������ʽ��BRE_TIM->BRE_LED_CCRx ���ɷ��ʸ�ͨ���ıȽϼĴ���
	#define BRE_LED_CCRx									CCR3
	#define BRE_LED_TIM_CHANNEL					TIM_Channel_3

	#define  BRE_TIM_OCxInit              TIM_OC3Init            //ͨ��ѡ��1~4
	#define  BRE_TIM_OCxPreloadConfig    TIM_OC3PreloadConfig 

#endif

void BreathLED_Config(void);

#endif /* __BREATH_LED_H */
