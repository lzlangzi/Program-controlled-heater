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


//�ҽ�E>10ʱ����ȫ�ټ��٣�E<=10ʱ��PID����