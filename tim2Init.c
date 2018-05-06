#include"include.h"
/*****************************************************************************
  * @function  : Tim2_Init
  * @brief     : TIM2初始化函数 CH2,3用作出LED的呼吸变化灯
  * @note      : STM8S105K
  * @param     : null
  * @retval    : null
             
******************************************************************************/
void Tim2_Init(void)                    //TIM2的初始化语句们
{
//         //配置通道1
//         TIM2_TimeBaseInit(TIM2_PRESCALER_8, 1999);              //第一步配置时基单元，先设置预分频PSCRH/L高低八位 寄存器，再设置自动装载寄存器ARRH/L。
//         TIM2_OC1Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,0,TIM2_OCPOLARITY_LOW);                      //然后配置通道的输出模式为PWM，启用输出比较，占空比设置为0，输出为低电平
//         TIM2_OC1PreloadConfig(ENABLE);
//         TIM2_Cmd(ENABLE); 
//
//
//         //配置通道2
//         TIM2_TimeBaseInit(TIM2_PRESCALER_8, 1999);              //第一步配置时基单元，先设置预分频PSCRH/L高低八位 寄存器，再设置自动装载寄存器ARRH/L。
//         TIM2_OC2Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_HIGH);                      //然后配置通道的输出模式为PWM，启用输出比较，占空比设置为0，输出为（低电平）
//         TIM2_OC2PreloadConfig(ENABLE);                          //开启预装载寄存器
//         TIM2_Cmd(ENABLE);                                       //最后的开启  启用定时器



        //配置通道3
        TIM2_TimeBaseInit(TIM2_PRESCALER_8, 1999);            //第一步配置时基单元，先设置预分频PSCRH/L高低八位 寄存器，再设置自动装载寄存器ARRH/L。
        TIM2_OC3Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_HIGH);                      //然后配置通道的输出模式为PWM，启用输出比较，占空比设置为0，输出为低电平
        TIM2_OC3PreloadConfig(ENABLE);
        TIM2_Cmd(ENABLE); 

}
/*****************************************************************************
  * @function  : Delay
  * @brief     : 延时
  * @note      : STM8S105K
  * @param     : null
  * @retval    : null
             
******************************************************************************/
void Delay(unsigned int time)
{
    while(time--);
}
