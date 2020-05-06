/* 该文件统一用于存放中断服务函数 */
#include "stm32f4xx.h"
#include "./adc/bsp_adc.h"

extern __IO uint16_t ADC_ConvertedValue;

// ADC 转换完成中断服务程序
void ADC_IRQHandler(void)
{
	if(ADC_GetITStatus(RHEOSTAT_ADC,ADC_IT_EOC)==SET)
	{
  // 读取ADC的转换值
		ADC_ConvertedValue = ADC_GetConversionValue(RHEOSTAT_ADC);

	}
	ADC_ClearITPendingBit(RHEOSTAT_ADC,ADC_IT_EOC);

}	

