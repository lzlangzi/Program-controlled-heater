#ifndef _clock_h_
#define _clock_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
//ʱ�ӷ�Ƶ��һЩ�궨��
#define HSIDIV1 (CLK_PRESCALER_HSIDIV1)
#define HSIDIV2 (CLK_PRESCALER_HSIDIV2)
#define HSIDIV4 (CLK_PRESCALER_HSIDIV4)
#define HSIDIV8 (CLK_PRESCALER_HSIDIV8)

#define CPUDIV1 (CLK_Prescaler_TypeDef)(CLK_PRESCALER_CPUDIV1)
#define CPUDIV2 (CLK_Prescaler_TypeDef)(CLK_PRESCALER_CPUDIV2)
#define CPUDIV4 (CLK_PRESCALER_CPUDIV4)
#define CPUDIV8 (CLK_PRESCALER_CPUDIV8)
#define CPUDIV16 (CLK_PRESCALER_CPUDIV16)
#define CPUDIV32 (CLK_PRESCALER_CPUDIV32)
#define CPUDIV64 (CLK_PRESCALER_CPUDIV64)
#define CPUDIV128 (CLK_PRESCALER_CPUDIV128)

extern void CLOCK_Hsi(CLK_Prescaler_TypeDef HsiDiv,CLK_Prescaler_TypeDef CpuDiv);
extern void CLOCK_Hse(CLK_Prescaler_TypeDef CpuDiv);
extern void CLOCK_Lsi(CLK_Prescaler_TypeDef CpuDiv);
#endif

/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/