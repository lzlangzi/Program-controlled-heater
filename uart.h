#ifndef _uart_h_
#define _uart_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
extern void UART_Init(void);
extern void Send_Dat(u8 dat);
extern void Send_Hex(unsigned char dat);
extern void Send_Str(unsigned char *dat);
#endif
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/