#ifndef __COLOR_LED_H
#define	__COLOR_LED_H

#include "stm32f4xx.h"


/********************��ʱ��ͨ��**************************/

#define COLOR_TIM           						TIM5
#define COLOR_TIM_CLK       						RCC_APB1Periph_TIM5
#define COLOR_TIM_APBxClock_FUN        RCC_APB1PeriphClockCmd

#define COLOR_TIM_GPIO_CLK             (RCC_AHB1Periph_GPIOH)


/************���***************/

#define COLOR_RED_PIN                  GPIO_Pin_10                 
#define COLOR_RED_GPIO_PORT            GPIOH                      
#define COLOR_RED_PINSOURCE						GPIO_PinSource10
#define COLOR_RED_AF										GPIO_AF_TIM5

#define  COLOR_RED_TIM_OCxInit                TIM_OC1Init            //ͨ����ʼ������
#define  COLOR_RED_TIM_OCxPreloadConfig       TIM_OC1PreloadConfig //ͨ���������ú���

//ͨ���ȽϼĴ�������TIMx->CCRx��ʽ�ɷ��ʸüĴ����������µıȽ�ֵ������ռ�ձ�
//�Ժ��װ��ʹ��������ʽ��COLOR_TIMx->COLOR_RED_CCRx ���ɷ��ʸ�ͨ���ıȽϼĴ���
#define  COLOR_RED_CCRx                       	CCR1		

/************�̵�***************/
#define COLOR_GREEN_PIN                  GPIO_Pin_11                 
#define COLOR_GREEN_GPIO_PORT            GPIOH                      
#define COLOR_GREEN_PINSOURCE						GPIO_PinSource11
#define COLOR_GREEN_AF										GPIO_AF_TIM5

#define  COLOR_GREEN_TIM_OCxInit                TIM_OC2Init            //ͨ����ʼ������
#define  COLOR_GREEN_TIM_OCxPreloadConfig       TIM_OC2PreloadConfig //ͨ���������ú���

//ͨ���ȽϼĴ�������TIMx->CCRx��ʽ�ɷ��ʸüĴ����������µıȽ�ֵ������ռ�ձ�
//�Ժ��װ��ʹ��������ʽ��COLOR_TIMx->COLOR_GREEN_CCRx ���ɷ��ʸ�ͨ���ıȽϼĴ���
#define  COLOR_GREEN_CCRx                       CCR2

/************����***************/
#define COLOR_BLUE_PIN                  GPIO_Pin_12                 
#define COLOR_BLUE_GPIO_PORT            GPIOH                       
#define COLOR_BLUE_PINSOURCE						GPIO_PinSource12
#define COLOR_BLUE_AF										GPIO_AF_TIM5

#define   COLOR_BLUE_TIM_OCxInit              TIM_OC3Init            //ͨ����ʼ������
#define   COLOR_BLUE_TIM_OCxPreloadConfig    TIM_OC3PreloadConfig  //ͨ���������ú���

//ͨ���ȽϼĴ�������TIMx->CCRx��ʽ�ɷ��ʸüĴ����������µıȽ�ֵ������ռ�ձ�
//�Ժ��װ��ʹ��������ʽ��COLOR_TIMx->COLOR_BLUE_CCRx ���ɷ��ʸ�ͨ���ıȽϼĴ���
#define   COLOR_BLUE_CCRx                      CCR3


/************************************************************/

/* RGB��ɫֵ 24λ*/
#define COLOR_WHITE          0xFFFFFF
#define COLOR_BLACK          0x000000
#define COLOR_GREY           0xC0C0C0
#define COLOR_BLUE           0x0000FF
#define COLOR_RED            0xFF0000
#define COLOR_MAGENTA        0xFF00FF
#define COLOR_GREEN          0x00FF00
#define COLOR_CYAN           0x00FFFF
#define COLOR_YELLOW         0xFFFF00


void ColorLED_Config(void);
void SetRGBColor(uint32_t rgb);
void SetColorValue(uint8_t r,uint8_t g,uint8_t b);

#endif /* __COLOR_LED_H */
