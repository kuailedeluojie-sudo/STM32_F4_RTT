#ifndef __ADVANCE_TIM_H
#define	__ADVANCE_TIM_H

#include "stm32f4xx.h"

/* ��ʱ�� */
#define ADVANCE_TIM           		    TIM8
#define ADVANCE_TIM_CLK       		    RCC_APB2Periph_TIM8

/* TIM8ͨ��1������� */
#define ADVANCE_OCPWM_PIN             GPIO_Pin_6              
#define ADVANCE_OCPWM_GPIO_PORT       GPIOC                      
#define ADVANCE_OCPWM_GPIO_CLK        RCC_AHB1Periph_GPIOC
#define ADVANCE_OCPWM_PINSOURCE				GPIO_PinSource6
#define ADVANCE_OCPWM_AF							GPIO_AF_TIM8

/* TIM8ͨ��1����������� */
#define ADVANCE_OCNPWM_PIN            GPIO_Pin_5              
#define ADVANCE_OCNPWM_GPIO_PORT      GPIOA                      
#define ADVANCE_OCNPWM_GPIO_CLK       RCC_AHB1Periph_GPIOA
#define ADVANCE_OCNPWM_PINSOURCE			GPIO_PinSource5
#define ADVANCE_OCNPWM_AF							GPIO_AF_TIM8

/* TIM8��·�������� */
#define ADVANCE_BKIN_PIN              GPIO_Pin_6              
#define ADVANCE_BKIN_GPIO_PORT        GPIOA                      
#define ADVANCE_BKIN_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define ADVANCE_BKIN_PINSOURCE	  		GPIO_PinSource6
#define ADVANCE_BKIN_AF						  	GPIO_AF_TIM8

void TIMx_Configuration(void);

#endif /* __ADVANCE_TIM_H */

