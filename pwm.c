/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/
#include "include.h"


/*******************************************************************************
****函数名称:
****函数功能:定时器2PWM初始化
****版本:V1.0
****日期:14-2-2014
****入口参数:timebase-时基，与产生的PWM频率有关
              t-高电平时间，与占空比有关
****出口参数:无
****说明:
********************************************************************************/
void TIMER2_PWMInit(unsigned short timebase,unsigned short t)
{
    TIM2_DeInit();  
    /*
     * TIM2 Frequency = TIM2 counter clock/(ARR + 1) 
     * 这里设置TIM2的计数频率为 16M/8/(timebase+1)=1K
     */
    TIM2_TimeBaseInit(TIM2_PRESCALER_8, timebase);	
    
    /* 
     * PWM1 Mode configuration: Channel1
     * TIM2 Channel1 duty cycle = [TIM2_CCR1/(TIM2_ARR + 1)] * 100 = 50%
     * TIM2 Channel2 duty cycle = [TIM2_CCR2/(TIM2_ARR + 1)] * 100 = 50%
     */ 
    
    /* 测试通道1 */
    TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, t, TIM2_OCPOLARITY_HIGH);
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_Cmd(ENABLE);
}
/*****************************************************************************
  * @function  : Tim2_Init
  * @brief     : TIM2初始化函数 CH2,3用作出LED的呼吸变化灯
  * @note      : STM8S105K
  * @param     : null
  * @retval    : null
             
******************************************************************************/
void Tim2_Init(void)                    //TIM2的初始化语句们
{       //配置通道3
        TIM2_TimeBaseInit(TIM2_PRESCALER_8, 1999);            //第一步配置时基单元，先设置预分频PSCRH/L高低八位 寄存器，再设置自动装载寄存器ARRH/L。
        TIM2_OC3Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_HIGH);                      //然后配置通道的输出模式为PWM，启用输出比较，占空比设置为0，输出为低电平
        TIM2_OC3PreloadConfig(ENABLE);
        TIM2_Cmd(ENABLE); 

}