#include "pid.h"




 float E = 0;
 float eo = 0;  
 float U;
extern u16 pwm ;
void Pid(float e)
{   
     
    

    pwm = (e * P+ eo * I)*1999/6/2/3+12;
    p = pwm/20;                 
    eo = e;
}


//我将E>10时启用全速加速，E<=10时用PID控制