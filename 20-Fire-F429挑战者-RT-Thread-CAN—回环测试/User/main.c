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


/*
*************************************************************************
*                               ����
*************************************************************************
*/
/* �����߳̿��ƿ� */
static rt_thread_t test_thread = RT_NULL;
/* �����ź������ƿ� */
rt_sem_t test_sem = RT_NULL;

__IO uint32_t flag = 0;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
CanTxMsg TxMessage;			     //���ͻ�����
CanRxMsg RxMessage;				 //���ջ�����

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
  /* ����һ���ź��� */
	test_sem = rt_sem_create("test_sem",/* ��Ϣ�������� */
                     0,     /* �ź�����ʼֵ��Ĭ����һ���ź��� */
                     RT_IPC_FLAG_FIFO); /* �ź���ģʽ FIFO(0x00)*/
  if (test_sem != RT_NULL)
    rt_kprintf("�ź��������ɹ���\n\n");
    
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
  rt_err_t uwRet = RT_EOK;	
   
  printf("\r\n ��ӭʹ��Ұ��  STM32 F429 �����塣\r\n");
  printf("\r\n Ұ��F429 CANͨѶ�ػ�ʵ������\r\n");
	
	printf("\r\n ʵ�鲽�裺\r\n");

	printf("\r\n 1.ʹ�ûػ�ģʽ������Ҫ�����ⲿоƬ\r\n");
	printf("\r\n 2.���¿������KEY1������ʹ��CAN���ⷢ��0-7�����ݰ���������չIDΪ0x1314 (���ڻػ�ģʽ�����Լ����͸��Լ�)\r\n");
	printf("\r\n 3.���������CAN���յ���չIDΪ0x1314�����ݰ�����������Դ�ӡ�����ڡ� \r\n");
	printf("\r\n 4.�����е�can������Ϊ1MBps��Ϊstm32��can������ʡ� \r\n");
  
  /* ������һ������ѭ�������ܷ��� */
  while (1)
  {
		/*��һ�ΰ�������һ������*/
	//	if(	Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
		{
			LED_BLUE;
			CAN_SetMsg(&TxMessage);
			
			CAN_Transmit(CANx, &TxMessage);
			
			rt_thread_delay(50);  //�ȴ�������ϣ���ʹ��CAN_TransmitStatus�鿴״̬
			
		//	LED_GREEN;
			
//			printf("\r\n��ʹ��CAN�������ݰ���\r\n"); 			
//			printf("\r\n���͵ı�������Ϊ��\r\n");
//			printf("\r\n ��չID��ExtId��0x%x \r\n",TxMessage.ExtId);
//			CAN_DEBUG_ARRAY(TxMessage.Data,8); 


		}
  //  printf("0x%x\n",RxMessage.StdId);
		uwRet = rt_sem_take(test_sem,	/* ��ȡ�����жϵ��ź��� */
                        0); 	  /* �ȴ�ʱ�䣺0 */
    if(RT_EOK == uwRet)
    {
	//		LED_GREEN;
			
			//printf("\r\nCAN���յ����ݣ�\r\n");	
				//StdId
			printf("0x%x\r\n",RxMessage.StdId);
			//ExtId
			printf("0x%x\r\n",RxMessage.ExtId);
			CAN_DEBUG_ARRAY(RxMessage.Data,8); 
    }
    
    rt_thread_delay(20);  	 		
  }
}

/********************************END OF FILE****************************/
