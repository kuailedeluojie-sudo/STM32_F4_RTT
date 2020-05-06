/* ���ļ�ͳһ���ڴ���жϷ����� */
#include "stm32f4xx.h"
#include "board.h" 

/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>

extern __IO uint32_t flag ;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
extern CanRxMsg RxMessage;				 //���ջ�����

/* �ⲿ�����ź������ƿ� */
extern rt_sem_t test_sem;

void CAN_RX_IRQHandler(void)
{
  /* �����ж� */
  rt_interrupt_enter();
  
	/*�������ж�������*/
	CAN_Receive(CANx, CAN_FIFO0, &RxMessage);

	/* �Ƚ�ID�Ƿ�Ϊ0x1314 */ 
//	if((RxMessage.ExtId==0x1314) && (RxMessage.IDE==CAN_ID_EXT) && (RxMessage.DLC==8) )
	if((RxMessage.StdId==0x0314) && (RxMessage.IDE==CAN_ID_STD) && (RxMessage.DLC==8) )
	{
   //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
   rt_sem_release(test_sem);  
	}
  
  /* �뿪�ж� */
  rt_interrupt_leave();

}

