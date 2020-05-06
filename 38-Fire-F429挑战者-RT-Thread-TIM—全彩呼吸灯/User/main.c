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

//该变量在定时器中断服务函数中使用，用于控制各通道的输出
//修改该变量的值可直接改变呼吸灯的颜色
//变量格式：RGB888
__IO uint32_t rgb_color = 0xFF00FF;

#define SOFT_DELAY() rt_thread_delay(200); 
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
  rt_kprintf("\r\n 欢迎使用秉火  STM32 F407 开发板。\r\n");		
  rt_kprintf("\r\n 呼吸灯例程\r\n");	  
  while (1)
  {
    
//    //			//可动态修改颜色，使用各种颜色的呼吸灯
//	  rgb_color = 0xFF00FF;
//		SOFT_DELAY();			

//		rgb_color =0x8080ff;
//		SOFT_DELAY();
//		
//		rgb_color =0xff8000;
//		SOFT_DELAY();
//		
//		rgb_color =0xffc90e;
//		SOFT_DELAY();
    
    rt_thread_delay(1000);   /* 延时 1000 个tick */
    rt_kprintf("\r\n RGB LED 以呼吸灯的形式闪烁\r\n ");
  }
}

/********************************END OF FILE****************************/
