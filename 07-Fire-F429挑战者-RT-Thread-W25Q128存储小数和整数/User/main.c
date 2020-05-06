/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 工程模版
  *********************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/ 
#include "board.h"
#include "rtthread.h"


/*
*************************************************************************
*                               变量
*************************************************************************
*/
//读取的ID存储位置
__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
	


/* 定义线程控制块 */
static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t test_thread = RT_NULL;
/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void led1_thread_entry(void* parameter);
static void test_thread_entry(void* parameter);


/*
*************************************************************************
*                             main 函数
*************************************************************************
*/
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
    /* 
	 * 开发板硬件初始化，RTT系统初始化已经在main函数之前完成，
	 * 即在component.c文件中的rtthread_startup()函数中完成了。
	 * 所以在main函数中，只需要创建线程和启动线程即可。
	 */
	
	led1_thread =                          /* 线程控制块指针 */
    rt_thread_create( "led1",              /* 线程名字 */
                      led1_thread_entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      512,                 /* 线程栈大小 */
                      2,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (led1_thread != RT_NULL)
        rt_thread_startup(led1_thread);
    else
        return -1;
		
	test_thread =                          /* 线程控制块指针 */
    rt_thread_create( "test",              /* 线程名字 */
                      test_thread_entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      1024,                 /* 线程栈大小 */
                      3,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (test_thread != RT_NULL)
        rt_thread_startup(test_thread);
    else
        return -1;
}

/*
*************************************************************************
*                             线程定义
*************************************************************************
*/

static void led1_thread_entry(void* parameter)
{	
    while (1)
    {
        LED1_ON;
        rt_thread_delay(500);   /* 延时500个tick */
        rt_kprintf("led1_thread running,LED1_ON\r\n");
        
        LED1_OFF;     
        rt_thread_delay(500);   /* 延时500个tick */		 		
        rt_kprintf("led1_thread running,LED1_OFF\r\n");
    }
}

static void test_thread_entry(void* parameter)
{	
	uint8_t cal_flag = 0;
	uint8_t k;
	
	/*存储小数和整数的数组，各7个*/
	long double double_buffer[7] = {0};
	int int_bufffer[7] = {0};

	LED_BLUE;
	
  
	printf("\r\n这是一个FLASH 读写小数和长整数实验 \r\n");
	
	/* 16M串行flash W25Q128初始化 */
	SPI_FLASH_Init();
	
	/* 获取 Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	
	rt_thread_delay( 200 );
	
	/* 获取 SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	
	printf("\r\nFlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	/* 检验 SPI Flash ID */
	if (FlashID == sFLASH_ID) 
	{	
		LED_GREEN;
		
		printf("\r\n检测到SPI FLASH W25Q128 !\r\n");
		
		/*读取数据标志位*/
    SPI_FLASH_BufferRead(&cal_flag, SPI_FLASH_PageSize*0, 1);
    
		if( cal_flag == 0xCD )	/*若标志等于0xcd，表示之前已有写入数据*/
    {
			  printf("\r\n检测到数据标志\r\n");

				/*读取小数数据*/
        SPI_FLASH_BufferRead((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
				
				/*读取整数数据*/
        SPI_FLASH_BufferRead((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
	
			
				printf("\r\n从芯片读到数据：\r\n");			
        for( k=0; k<7; k++ )
				{
					printf("小数 rx = %LF \r\n",double_buffer[k]);
					printf("整数 rx = %d \r\n",int_bufffer[k]);				
				}
    }    
    else
    {
      printf("\r\n没有检测到数据标志，FLASH没有存储数据，即将进行小数写入实验\r\n");
			cal_flag =0xCD;
			/*擦除扇区*/
      SPI_FLASH_SectorErase(0);
			
			/*写入标志到第0页*/
      SPI_FLASH_BufferWrite(&cal_flag, SPI_FLASH_PageSize*0, 1); 
      
			/*生成要写入的数据*/
      for( k=0; k<7; k++ )
			{
			   double_buffer[k] = k +0.1;
				 int_bufffer[k]=k*500+1 ;
			}

			/*写入小数数据到第一页*/
      SPI_FLASH_BufferWrite((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
			/*写入整数数据到第二页*/
      SPI_FLASH_BufferWrite((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
       			
			printf("向芯片写入数据：");
			/*打印到串口*/
      for( k=0; k<7; k++ )
			{
        printf("小数tx = %LF\r\n",double_buffer[k]);
				printf("整数tx = %d\r\n",int_bufffer[k]);
			}
			
			printf("\r\n请复位开发板，以读取数据进行检验\r\n");
    }   

	}// if (FlashID == sFLASH_ID)
	else
	{    
		LED_RED;
		printf("\r\n获取不到 W25Q128 ID!\n\r");
	}
	
	SPI_Flash_PowerDown();  
	while (1)
	{
    LED2_TOGGLE;
		rt_thread_delay(1000);   /* 延时500个tick */		 		

	}
}


/********************************END OF FILE****************************/
