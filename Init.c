#include "stm8s.h"
#include "pwm.h"
#include "uart.h"
#include "delay.h"
#include "clock.h"
#include "oled_iic.h"
#include "init.h"



void Init_All()
{
  
      CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//16M
     
      Delay_Init(16);

      Tim2_Init();                        //再初始化TIM2 PWM1输出模式    

      Oled_init();                        //oled

      enableInterrupts();                //enable
      

     

}

