#ifndef _key_h_
#define _key_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
//���尴���ӿ�
#define KEY1_GPIO_PORT  (GPIOB)
#define KEY1_GPIO_PINS  (GPIO_PIN_3)

#define KEY2_GPIO_PORT  (GPIOD)
#define KEY2_GPIO_PINS  (GPIO_PIN_3)

#define KEY3_GPIO_PORT  (GPIOD)
#define KEY3_GPIO_PINS  (GPIO_PIN_7)
//  ����KEY����
#define  KEY1       0x01
#define  KEY2       0x02
#define  KEY3       0x04
extern void KEY_Init(u8 KeyNum);
extern u8 KEY_Get(u8 KeyNum);
#endif
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/