/* ������Ӳ�����ͷ�ļ� */
#include "board.h" 

/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>


#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 1024
/* ���ڲ�SRAM�������һ���־�̬�ڴ�����Ϊrtt�Ķѿռ䣬��������Ϊ4KB */
static uint32_t rt_heap[RT_HEAP_SIZE];
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
  * @brief  ������Ӳ����ʼ������
  * @param  ��
  * @retval ��
  *
  * @attention
  * RTT�ѿ�������صĳ�ʼ������ͳһ�ŵ�board.c�ļ���ʵ�֣�
  * ��Ȼ���������Щ����ͳһ�ŵ�main.c�ļ�Ҳ�ǿ��Եġ�
  */
void rt_hw_board_init()
{
    /* ��ʼ��SysTick */
    SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );	
    
	/* Ӳ��BSP��ʼ��ͳͳ�����������LED�����ڣ�LCD�� */
    
    /* ��ʼ���������LED */
	LED_GPIO_Config();
  BEEP_GPIO_Config();  
    /* ��ʼ��������Ĵ��� */
	Debug_USART_Config();
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
		/* �������� */
		RTC_AlarmSet();
		
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

    /* ���RTC�жϱ�־λ */
    RTC_ClearFlag(RTC_FLAG_ALRAF);
    /* ��� EXTI Line 17 ����λ (�ڲ����ӵ�RTC Alarm) */
    EXTI_ClearITPendingBit(EXTI_Line17);		
  } 
	
/* ���������ʼ������ (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

/**
  * @brief  SysTick�жϷ�����
  * @param  ��
  * @retval ��
  *
  * @attention
  * SysTick�жϷ������ڹ̼����ļ�stm32f10x_it.c��Ҳ�����ˣ�������
  * ��board.c���ֶ���һ�Σ���ô�����ʱ�������ظ�����Ĵ��󣬽��
  * �����ǿ��԰�stm32f10x_it.c�е�ע�ͻ���ɾ�����ɡ�
  */
void SysTick_Handler(void)
{
    /* �����ж� */
    rt_interrupt_enter();

    /* ����ʱ�� */
    rt_tick_increase();

    /* �뿪�ж� */
    rt_interrupt_leave();
}



/**
  * @brief  ��ӳ�䴮��DEBUG_USARTx��rt_kprintf()����
  *   Note��DEBUG_USARTx����bsp_usart.h�ж���ĺ꣬Ĭ��ʹ�ô���1
  * @param  str��Ҫ��������ڵ��ַ���
  * @retval ��
  *
  * @attention
  * 
  */
void rt_hw_console_output(const char *str)
{	
	/* �����ٽ�� */
    rt_enter_critical();

	/* ֱ���ַ������� */
    while (*str!='\0')
	{
		/* ���� */
        if (*str=='\n')
		{
			USART_SendData(DEBUG_USART, '\r'); 
			while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);
		}

		USART_SendData(DEBUG_USART, *str++); 				
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);	
	}	

	/* �˳��ٽ�� */
    rt_exit_critical();
}
