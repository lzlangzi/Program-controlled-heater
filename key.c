/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "include.h"



/*******************************************************************************
****��������:
****��������:��ʼ��KEY�ӿ�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ʼ����LED
ȡֵ����ֵ֮һ��������֮��ġ������㡱�����ʽ
            KEY1
            KEY2
            KEY3
****���ڲ���:��
****˵��:
********************************************************************************/
void KEY_Init(u8 KeyNum)
{
   if(KeyNum&KEY1)
   {
        GPIO_Init(KEY1_GPIO_PORT, KEY1_GPIO_PINS, GPIO_MODE_IN_FL_NO_IT);
   }
   if(KeyNum&KEY2)
   {
        GPIO_Init(KEY2_GPIO_PORT, KEY2_GPIO_PINS, GPIO_MODE_IN_FL_NO_IT);
   }
   if(KeyNum&KEY3)
   {
        GPIO_Init(KEY3_GPIO_PORT, KEY3_GPIO_PINS, GPIO_MODE_IN_FL_NO_IT);
   }
}
/*******************************************************************************
****��������:
****��������:���ؼ�ֵ
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ʼ����LED
ȡֵ����ֵ֮һ��������֮��ġ������㡱�����ʽ
            KEY1
            KEY2
            KEY3
****���ڲ���:��ֵ
KEY1/KEY2/KEY2��λ�����ʽ�������м������
            0x00    û�а�������
            0x01    KEY1������
            0x02    KEY2������
            0x03    KEY1��KEY2��������
            0x04    KEY3������
            0x05    KEY1��KEY3������
            0x06    KEY2��KEY3������
            0x07    KEY1/KEY2/KEY3��������
****˵��:
********************************************************************************/
u8 KEY_Get(u8 KeyNum)
{
  u8 KeyValue=0x00;
  if(KeyNum&KEY1)
  {
    if( GPIO_ReadInputPin(KEY1_GPIO_PORT, KEY1_GPIO_PINS)==RESET)
      KeyValue|=0x01;
  }
  if(KeyNum&KEY2)
  {
    if( GPIO_ReadInputPin(KEY2_GPIO_PORT, KEY2_GPIO_PINS)==RESET)
      KeyValue|=0x02;
  }
  if(KeyNum&KEY3)
  {
    if( GPIO_ReadInputPin(KEY3_GPIO_PORT, KEY3_GPIO_PINS)==RESET)
      KeyValue|=0x04;
  }
  return KeyValue;
}
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/