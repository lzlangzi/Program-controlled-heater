#include "heater.h"

u16 pwm = 0;
extern u16   fan_flag, p, speed, pwm;//t_flag,
extern float temperature_read, E,temperature;

/*******************************************************************************
* 函 数 名       : Heater_Init
* 函数功能       : 初始化加热器
* 输    入       : 无
* 输    出    	 : 无
* 备    注	 : 
*******************************************************************************/
void Heater_Init()
{
    if(temperature>temperature_read)
    {
        
        E = temperature - temperature_read ;//差值
    }
    else
    {
        E = 0;//差值
        pwm = 0;
    }
    
    if( E > 0)
    {
      if( E > 10)
      {
        if(temperature>temperature_read)
        {
          p = 100;
          pwm = 400;
        }
        else p = 0, pwm = 0;
      }
      else 
      {
           Pid(E);
  
      }
    
    }

    

    if(temperature_read <30)
    {

        p = 100;
        fan_flag = 0;

    }
    
    if(temperature_read >= 70)
    {
        p = 0;
        fan_flag = 1;
        TIM2_SetCompare2(0);

    }       

      TIM2_SetCompare3(1999-pwm);

    if(temperature<=(temperature_read-0.12))
    {
      TIM2_SetCompare2(1699);
    }
}























//    if(fan_flag == 1)
//    {
//        if(speed == 100)
//        {
//            TIM2_SetCompare3(0);
//        }
//        else TIM2_SetCompare3(1999-speed*20);
//    }
//    else 
//    {
//        TIM2_SetCompare3(1999);
//        
//    }