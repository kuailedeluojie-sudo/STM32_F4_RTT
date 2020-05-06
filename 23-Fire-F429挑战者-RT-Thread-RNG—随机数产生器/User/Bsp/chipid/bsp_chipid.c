/**
  ******************************************************************************
  * @file    bsp_beep.c
  * @author  fire
  * @version V3.0
  * @date    2015-xx-xx
  * @brief   ��ȡchipid ��Ƭ��FLASH��С��Ӧ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� STM32  F429������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

//��ȡCPU��ID������ÿ��оƬ����Ψһ�� 96_bit unique ID         

#include "./chipid/bsp_chipid.h"



/*
 * ��������Get_ChipID
 * ����  ����ȡоƬID
 * ����  ��chip_id:�洢оƬID�Ľṹ��
 * ���  ����
 */
void Get_ChipID(CHIP_ID_TypeDef* chip_id)  
{
		
	chip_id->ID_H = CHIP_ID->ID_H;
	chip_id->ID_M = CHIP_ID->ID_M; 
	chip_id->ID_L = CHIP_ID->ID_L;	
	
//	printf("\r\nchipID=0x%08x%08x%08x", CHIP_ID->ID_H,CHIP_ID->ID_M,CHIP_ID->ID_L);	

}


/*
 * ��������Get_ChipFlashSize
 * ����  ����ȡоƬFLASH��С����λΪKB
 * ����  ����
 * ���  ��оƬFLASH��С����λΪKB
 */
uint32_t Get_ChipFlashSize(void) 
{
	//��16λΪFLASH ��С
	return (CHIP_FLASH_SIZE &0xFFFF); 
}

/*********************************************END OF FILE**********************/

