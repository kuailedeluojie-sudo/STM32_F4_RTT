/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 �̼�������
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
#include "board.h"
#include "rtthread.h"


/*
*************************************************************************
*                               ����
*************************************************************************
*/
/* �����߳̿��ƿ� */
static rt_thread_t test_thread = RT_NULL;

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[2];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[2]; 


/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void test_thread_entry(void* parameter);


/*
*************************************************************************
*                             main ����
*************************************************************************
*/
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
    /* 
	 * ������Ӳ����ʼ����RTTϵͳ��ʼ���Ѿ���main����֮ǰ��ɣ�
	 * ����component.c�ļ��е�rtthread_startup()����������ˡ�
	 * ������main�����У�ֻ��Ҫ�����̺߳������̼߳��ɡ�
	 */
	
	test_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "test",              /* �߳����� */
                      test_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      512,                 /* �߳�ջ��С */
                      3,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (test_thread != RT_NULL)
        rt_thread_startup(test_thread);
    else
        return -1;
}

/*
*************************************************************************
*                             �̶߳���
*************************************************************************
*/

static void test_thread_entry(void* parameter)
{	
  printf("\r\n ----����һ�����������ѹ�ɼ�ʵ��(DMA����)----\r\n");

  Rheostat_Init();
  while (1)
  {
    ADC_ConvertedValueLocal[0] =(float)((uint16_t)ADC_ConvertedValue[0]*3.3/4096); 
    ADC_ConvertedValueLocal[1] =(float)((uint16_t)ADC_ConvertedValue[1]*3.3/4096);    
    
    printf("\r\n The current AD value = 0x%08X \r\n", ADC_ConvertedValue[0]); 
    printf("\r\n The current AD value = 0x%08X \r\n", ADC_ConvertedValue[1]);     
    
    printf("\r\n The current ADC1 value = %f V \r\n",ADC_ConvertedValueLocal[0]); 
    printf("\r\n The current ADC2 value = %f V \r\n",ADC_ConvertedValueLocal[1]);    
  
		rt_thread_delay(1000);   /* ��ʱ500��tick */			

  }
}

/********************************END OF FILE****************************/
