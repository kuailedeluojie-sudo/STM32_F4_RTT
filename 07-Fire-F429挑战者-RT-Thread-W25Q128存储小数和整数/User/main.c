/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 ����ģ��
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
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
//��ȡ��ID�洢λ��
__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
	


/* �����߳̿��ƿ� */
static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t test_thread = RT_NULL;
/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void led1_thread_entry(void* parameter);
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
	
	led1_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "led1",              /* �߳����� */
                      led1_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      512,                 /* �߳�ջ��С */
                      2,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (led1_thread != RT_NULL)
        rt_thread_startup(led1_thread);
    else
        return -1;
		
	test_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "test",              /* �߳����� */
                      test_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      1024,                 /* �߳�ջ��С */
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

static void led1_thread_entry(void* parameter)
{	
    while (1)
    {
        LED1_ON;
        rt_thread_delay(500);   /* ��ʱ500��tick */
        rt_kprintf("led1_thread running,LED1_ON\r\n");
        
        LED1_OFF;     
        rt_thread_delay(500);   /* ��ʱ500��tick */		 		
        rt_kprintf("led1_thread running,LED1_OFF\r\n");
    }
}

static void test_thread_entry(void* parameter)
{	
	uint8_t cal_flag = 0;
	uint8_t k;
	
	/*�洢С�������������飬��7��*/
	long double double_buffer[7] = {0};
	int int_bufffer[7] = {0};

	LED_BLUE;
	
  
	printf("\r\n����һ��FLASH ��дС���ͳ�����ʵ�� \r\n");
	
	/* 16M����flash W25Q128��ʼ�� */
	SPI_FLASH_Init();
	
	/* ��ȡ Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	
	rt_thread_delay( 200 );
	
	/* ��ȡ SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	
	printf("\r\nFlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	/* ���� SPI Flash ID */
	if (FlashID == sFLASH_ID) 
	{	
		LED_GREEN;
		
		printf("\r\n��⵽SPI FLASH W25Q128 !\r\n");
		
		/*��ȡ���ݱ�־λ*/
    SPI_FLASH_BufferRead(&cal_flag, SPI_FLASH_PageSize*0, 1);
    
		if( cal_flag == 0xCD )	/*����־����0xcd����ʾ֮ǰ����д������*/
    {
			  printf("\r\n��⵽���ݱ�־\r\n");

				/*��ȡС������*/
        SPI_FLASH_BufferRead((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
				
				/*��ȡ��������*/
        SPI_FLASH_BufferRead((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
	
			
				printf("\r\n��оƬ�������ݣ�\r\n");			
        for( k=0; k<7; k++ )
				{
					printf("С�� rx = %LF \r\n",double_buffer[k]);
					printf("���� rx = %d \r\n",int_bufffer[k]);				
				}
    }    
    else
    {
      printf("\r\nû�м�⵽���ݱ�־��FLASHû�д洢���ݣ���������С��д��ʵ��\r\n");
			cal_flag =0xCD;
			/*��������*/
      SPI_FLASH_SectorErase(0);
			
			/*д���־����0ҳ*/
      SPI_FLASH_BufferWrite(&cal_flag, SPI_FLASH_PageSize*0, 1); 
      
			/*����Ҫд�������*/
      for( k=0; k<7; k++ )
			{
			   double_buffer[k] = k +0.1;
				 int_bufffer[k]=k*500+1 ;
			}

			/*д��С�����ݵ���һҳ*/
      SPI_FLASH_BufferWrite((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
			/*д���������ݵ��ڶ�ҳ*/
      SPI_FLASH_BufferWrite((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
       			
			printf("��оƬд�����ݣ�");
			/*��ӡ������*/
      for( k=0; k<7; k++ )
			{
        printf("С��tx = %LF\r\n",double_buffer[k]);
				printf("����tx = %d\r\n",int_bufffer[k]);
			}
			
			printf("\r\n�븴λ�����壬�Զ�ȡ���ݽ��м���\r\n");
    }   

	}// if (FlashID == sFLASH_ID)
	else
	{    
		LED_RED;
		printf("\r\n��ȡ���� W25Q128 ID!\n\r");
	}
	
	SPI_Flash_PowerDown();  
	while (1)
	{
    LED2_TOGGLE;
		rt_thread_delay(1000);   /* ��ʱ500��tick */		 		

	}
}


/********************************END OF FILE****************************/
