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
****��������:ϵͳʱ���л���HSI
****�汾:V1.0
****����:14-2-2014
****��ڲ���:HsiDiv-HSI��Ƶ��;CpuDiv-ϵͳʱ�ӷ�Ƶ
****���ڲ���:��
****˵��:
********************************************************************************/
void CLOCK_Hsi(CLK_Prescaler_TypeDef HsiDiv,CLK_Prescaler_TypeDef CpuDiv)
{
   CLK_HSICmd(ENABLE);  //ʹ��HSI
  
   while(CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE)==ERROR);//�л�����
   while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY)==RESET); //HSI�Ƿ����
   CLK_ClockSwitchCmd(ENABLE);//ʹ���л�

   CLK_HSIPrescalerConfig(HsiDiv);//��Ƶ����
   CLK_SYSCLKConfig(CpuDiv);      //ʹ��ʱ�Ӱ�ȫ
}
/*******************************************************************************
****��������:
****��������:ϵͳʱ���л���HSE
****�汾:V1.0
****����:14-2-2014
****��ڲ���:CpuDiv-ϵͳʱ�ӷ�Ƶ
****���ڲ���:��
****˵��:
********************************************************************************/
void CLOCK_Hse(CLK_Prescaler_TypeDef CpuDiv)
{
    CLK_HSECmd(ENABLE);//ʹ��HSE
    while(CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE)==ERROR);//�л�����
    while(CLK_GetFlagStatus(CLK_FLAG_HSERDY)==RESET);//�ȴ�HSE����
    
    CLK_ClockSwitchCmd(ENABLE);//�л� 
   
    CLK_ClockSecuritySystemEnable();//ʹ��ʱ�Ӱ�ȫ
    CLK_SYSCLKConfig(CpuDiv);//��Ƶ����

}
/*******************************************************************************
****��������:
****��������:ϵͳʱ���л���LSI
****�汾:V1.0
****����:14-2-2014
****��ڲ���:CpuDiv-ϵͳʱ�ӷ�Ƶ
****���ڲ���:��
****˵��:LSI��Ҫ����OPTIONBYTE��Ӧλ
********************************************************************************/
void CLOCK_Lsi(CLK_Prescaler_TypeDef CpuDiv)
{
    CLK_LSICmd(ENABLE);//ʹ��LSI
    
    while(CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_LSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE)==ERROR);//�л�����
    while(CLK_GetFlagStatus(CLK_FLAG_LSIRDY)==RESET);//�ȴ�LSI����
   
    CLK_ClockSwitchCmd(ENABLE);//ʹ���л�
    CLK_SYSCLKConfig(CpuDiv);  //��Ƶ

}

/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/