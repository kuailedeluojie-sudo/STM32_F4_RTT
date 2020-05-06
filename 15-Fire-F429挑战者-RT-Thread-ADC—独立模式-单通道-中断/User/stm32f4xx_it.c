/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f4xx.h"
#include "./adc/bsp_adc.h"

extern __IO uint16_t ADC_ConvertedValue;

// ADC ת������жϷ������
void ADC_IRQHandler(void)
{
	if(ADC_GetITStatus(RHEOSTAT_ADC,ADC_IT_EOC)==SET)
	{
  // ��ȡADC��ת��ֵ
		ADC_ConvertedValue = ADC_GetConversionValue(RHEOSTAT_ADC);

	}
	ADC_ClearITPendingBit(RHEOSTAT_ADC,ADC_IT_EOC);

}	

