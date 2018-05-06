#include "include.h"

int hz = 1;

/*******************************************************************************
****函数名称:
****函数功能:初始化LED接口
****版本:V1.0
****日期:14-2-2014
****入口参数:需要初始化的LED
取值下列值之一或者它们之间的“或运算”组合形式
            LED1
            LED2
            LED3
****出口参数:无
****说明:
********************************************************************************/
void LED_Init(u8 LedNum)
{
   if(LedNum&LED1)
   {
      GPIO_Init(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
   }
    if(LedNum&LED2)
   {
      GPIO_Init(LED2_GPIO_PORT, (GPIO_Pin_TypeDef)LED2_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
   }
    if(LedNum&LED3)
   {
      GPIO_Init(LED3_GPIO_PORT, (GPIO_Pin_TypeDef)LED3_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
   }
}
/*******************************************************************************
****函数名称:
****函数功能:点亮LED
****版本:V1.0
****日期:14-2-2014
****入口参数:需要点亮的LED
取值下列值之一或者它们之间的“或运算”组合形式
            LED1
            LED2
            LED3
****出口参数:无
****说明:
********************************************************************************/
void LED_On(u8 LedNum)
{
   if(LedNum&LED1)
   {
      GPIO_WriteLow(LED1_GPIO_PORT, LED1_GPIO_PINS);
   }
   if(LedNum&LED2)
   {
      GPIO_WriteLow(LED2_GPIO_PORT, LED2_GPIO_PINS);
   }
   if(LedNum&LED3)
   {
      GPIO_WriteLow(LED3_GPIO_PORT, LED3_GPIO_PINS);
   }
}
/*******************************************************************************
****函数名称:
****函数功能:熄灭LED
****版本:V1.0
****日期:14-2-2014
****入口参数:需要熄灭的LED
取值下列值之一或者它们之间的“或运算”组合形式
            LED1
            LED2
            LED3
****出口参数:无
****说明:
********************************************************************************/
void LED_Off(u8 LedNum)
{
   if(LedNum&LED1)
   {
      GPIO_WriteHigh(LED1_GPIO_PORT, LED1_GPIO_PINS);
   }
   if(LedNum&LED2)
   {
      GPIO_WriteHigh(LED2_GPIO_PORT, LED2_GPIO_PINS);
   }
   if(LedNum&LED3)
   {
      GPIO_WriteHigh(LED3_GPIO_PORT, LED3_GPIO_PINS);
   }
}
/*******************************************************************************
****函数名称:
****函数功能:翻转LED
****版本:V1.0
****日期:14-2-2014
****入口参数:需要翻转的LED
取值下列值之一或者它们之间的“或运算”组合形式
            LED1
            LED2
            LED3
****出口参数:无
****说明:
********************************************************************************/
void LED_Toggle(u8 LedNum)
{
   if(LedNum&LED1)
   {
      GPIO_WriteReverse(LED1_GPIO_PORT, LED1_GPIO_PINS);
   }
   if(LedNum&LED2)
   {
      GPIO_WriteReverse(LED2_GPIO_PORT, LED2_GPIO_PINS);
   }
   if(LedNum&LED3)
   {
      GPIO_WriteReverse(LED3_GPIO_PORT, LED3_GPIO_PINS);
   }
}
/*******************************************************************************
****函数名称:
****函数功能:呼吸灯
****版本:V1.0
****日期:18-3-2017
****入口参数:无
****出口参数:无
****说明:
********************************************************************************/
void LED_Breath(void)
{
   static int sta = 0,PWM = 0;
    

         // IWDG_ReloadCounter();//喂狗

          if((!sta) && (PWM<2000))      //比较好的循环

          {
            PWM += hz;                             //关于频率可以改变这里
          }
          if(PWM >= 2000) 
          {
            sta = 1;

          }
          if((sta) && (PWM>0))
          {
            PWM -= hz;
            if(PWM <= 0) sta = 0;
          }

          Delay(1500);                   //延时调整呼吸的速度
       
          TIM2_SetCompare3(PWM);
          
         


    
}
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/