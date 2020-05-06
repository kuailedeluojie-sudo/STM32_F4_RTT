/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 固件库例程
  *********************************************************************
  * @attention
  *
  * 实验平台:野火  STM32F407 开发板 
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
/* 定义线程控制块 */
static rt_thread_t test_thread = RT_NULL;

/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
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
	
	test_thread =                          /* 线程控制块指针 */
    rt_thread_create( "test",              /* 线程名字 */
                      test_thread_entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      512,                 /* 线程栈大小 */
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

static void test_thread_entry(void* parameter)
{	
 
	LED_BLUE;
	/*调用printf函数，因为重定向了fputc，printf的内容会输出到串口*/
  printf("this is a usart printf demo. \r\n");
	printf("\r\n 欢迎使用野火  STM32 F429 开发板。\r\n");	
	printf("正在进行读写内部FLASH实验，请耐心等待\r\n");
	
	if(InternalFlash_Test()==0)
	{
		LED_GREEN;
		printf("读写内部FLASH测试成功\r\n");

	}
	else
	{
		printf("读写内部FLASH测试失败\r\n");
		LED_RED;
	}
  
  while (1)
  {
    LED1_ON;
    rt_thread_delay(500);   /* 延时500个tick */
    rt_kprintf("test_thread running,LED1_ON\r\n");
    
    LED1_OFF;     
    rt_thread_delay(500);   /* 延时500个tick */		 		
    rt_kprintf("test_thread running,LED1_OFF\r\n");
  }
}

/********************************END OF FILE****************************/
