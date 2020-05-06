#ifndef __BREATH_LED_H
#define	__BREATH_LED_H

#include "stm32f4xx.h"

/*��ѹ��ֵ�ȼ���*/
#define AMPLITUDE_CLASS 256

//����������ε�Ƶ��
extern __IO uint16_t period_class ;

/*PWM���еĵ���*/
extern uint16_t POINT_NUM;



/********************��ʱ��ͨ��**************************/


#define BRE_TIM           							TIM5
#define BRE_TIM_CLK       						RCC_APB1Periph_TIM5
#define BRE_TIM_GPIO_CLK              (RCC_AHB1Periph_GPIOH)
#define BRE_TIM_APBxClock_FUN        RCC_APB1PeriphClockCmd

#define BRE_TIM_IRQn								TIM5_IRQn
#define BRE_TIM_IRQHandler 				TIM5_IRQHandler

//R ��ɫ��
#define BRE_RED_PIN                  GPIO_Pin_10                 
#define BRE_RED_GPIO_PORT            GPIOH                      
#define BRE_RED_PINSOURCE							GPIO_PinSource10
#define BRE_RED_AF										GPIO_AF_TIM5

//ͨ���ȽϼĴ�������TIMx->CCRx��ʽ�ɷ��ʸüĴ����������µıȽ�ֵ������ռ�ձ�
//�Ժ��װ��ʹ��������ʽ��BRE_TIM->BRE_RED_CCRx ���ɷ��ʸ�ͨ���ıȽϼĴ���
#define BRE_RED_CCRx									CCR1
#define BRE_RED_TIM_CHANNEL					TIM_Channel_1

#define  BRE_RED_TIM_OCxInit              TIM_OC1Init            //ͨ��ѡ��1~4
#define  BRE_RED_TIM_OCxPreloadConfig    TIM_OC1PreloadConfig 


//G ��ɫ��
#define BRE_GREEN_PIN                  GPIO_Pin_11                 
#define BRE_GREEN_GPIO_PORT            GPIOH                      
#define BRE_GREEN_PINSOURCE							GPIO_PinSource11
#define BRE_GREEN_AF										GPIO_AF_TIM5

//ͨ���ȽϼĴ�������TIMx->CCRx��ʽ�ɷ��ʸüĴ����������µıȽ�ֵ������ռ�ձ�
//�Ժ��װ��ʹ��������ʽ��BRE_TIM->BRE_GREEN_CCRx ���ɷ��ʸ�ͨ���ıȽϼĴ���
#define BRE_GREEN_CCRx									CCR2
#define BRE_GREEN_TIM_CHANNEL					TIM_Channel_2

#define  BRE_GREEN_TIM_OCxInit              TIM_OC2Init            //ͨ��ѡ��1~4
#define  BRE_GREEN_TIM_OCxPreloadConfig    TIM_OC2PreloadConfig 

//B ��ɫ��
#define BRE_BLUE_PIN                  GPIO_Pin_12                 
#define BRE_BLUE_GPIO_PORT            GPIOH                      
#define BRE_BLUE_PINSOURCE							GPIO_PinSource12
#define BRE_BLUE_AF										GPIO_AF_TIM5

#define BRE_BLUE_CCRx									CCR3
#define BRE_BLUE_TIM_CHANNEL					TIM_Channel_3

#define  BRE_BLUE_TIM_OCxInit              TIM_OC3Init            //ͨ��ѡ��1~4
#define  BRE_BLUE_TIM_OCxPreloadConfig    TIM_OC3PreloadConfig 


void BreathLED_Config(void);

#endif /* __BREATH_LED_H */
