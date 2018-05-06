#ifndef    __PID_H_
#define    __PID_H_

#include "stm8s.h"


//#define  D 
float P=0.5, I = 0.1;
extern u16 p;
void Pid(float e);

#endif