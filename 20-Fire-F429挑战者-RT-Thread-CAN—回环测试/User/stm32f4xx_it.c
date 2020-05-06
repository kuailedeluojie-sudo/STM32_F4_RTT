/* 该文件统一用于存放中断服务函数 */
#include "stm32f4xx.h"
#include "board.h" 

/* RT-Thread相关头文件 */
#include <rthw.h>
#include <rtthread.h>

extern __IO uint32_t flag ;		 //用于标志是否接收到数据，在中断函数中赋值
extern CanRxMsg RxMessage;				 //接收缓冲区

/* 外部定义信号量控制块 */
extern rt_sem_t test_sem;

void CAN_RX_IRQHandler(void)
{
  /* 进入中断 */
  rt_interrupt_enter();
  
	/*从邮箱中读出报文*/
	CAN_Receive(CANx, CAN_FIFO0, &RxMessage);

	/* 比较ID是否为0x1314 */ 
//	if((RxMessage.ExtId==0x1314) && (RxMessage.IDE==CAN_ID_EXT) && (RxMessage.DLC==8) )
	if((RxMessage.StdId==0x0314) && (RxMessage.IDE==CAN_ID_STD) && (RxMessage.DLC==8) )
	{
   //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
   rt_sem_release(test_sem);  
	}
  
  /* 离开中断 */
  rt_interrupt_leave();

}

