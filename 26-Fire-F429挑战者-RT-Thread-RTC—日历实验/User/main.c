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
  * ʵ��ƽ̨:Ұ��  STM32F407 ������ 
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

#ifdef USE_LCD_DISPLAY
	#include "./lcd/bsp_lcd.h"
#endif

/*
*************************************************************************
*                               ����
*************************************************************************
*/
/* �����߳̿��ƿ� */
static rt_thread_t test_thread = RT_NULL;

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
	printf("\n\r����һ��RTC����ʵ�� \r\n");
	
	/*=========================Һ����ʼ����ʼ===============================*/
	LCD_Init();
  LCD_LayerInit();
  LTDC_Cmd(ENABLE);
	
	/*�ѱ�����ˢ��ɫ*/
  LCD_SetLayer(LCD_BACKGROUND_LAYER);  
	LCD_Clear(LCD_COLOR_BLACK);
	
  /*��ʼ����Ĭ��ʹ��ǰ����*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER); 
	/*Ĭ�����ò�͸��	���ú�������Ϊ��͸���ȣ���Χ 0-0xff ��0Ϊȫ͸����0xffΪ��͸��*/
  LCD_SetTransparency(0xFF);
	LCD_Clear(LCD_COLOR_BLACK);
	/*����LCD_SetLayer(LCD_FOREGROUND_LAYER)������
	����Һ����������ǰ����ˢ�£��������µ��ù�LCD_SetLayer�������ñ�����*/		
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
 /*=========================Һ����ʼ������===============================*/
	
	/*
	 * ���������ù�RTCʱ��֮��������ݼĴ���0д��һ�����������
	 * ����ÿ�γ����������е�ʱ���ͨ����ⱸ�ݼĴ���0��ֵ���ж�
	 * RTC �Ƿ��Ѿ����ù���������ù��Ǿͼ������У����û�����ù�
	 * �ͳ�ʼ��RTC������RTC��ʱ�䡣
	 */
   
  /* RTC���ã�ѡ��ʱ��Դ������RTC_CLK�ķ�Ƶϵ�� */
  RTC_CLK_Config();

  if (RTC_ReadBackupRegister(RTC_BKP_DRX) != RTC_BKP_DATA)
  {
    /* ����ʱ������� */
		RTC_TimeAndDate_Set();
  }
  else
  {
    /* ����Ƿ��Դ��λ */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      printf("\r\n ������Դ��λ....\r\n");
    }
    /* ����Ƿ��ⲿ��λ */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      printf("\r\n �����ⲿ��λ....\r\n");
    }

    printf("\r\n ����Ҫ��������RTC....\r\n");
    
    /* ʹ�� PWR ʱ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    /* PWR_CR:DBF��1��ʹ��RTC��RTC���ݼĴ����ͱ���SRAM�ķ��� */
    PWR_BackupAccessCmd(ENABLE);
    /* �ȴ� RTC APB �Ĵ���ͬ�� */
    RTC_WaitForSynchro();   
  } 
	
	/* ��ʾʱ������� */
	RTC_TimeAndDate_Show();
  
}

/********************************END OF FILE****************************/
