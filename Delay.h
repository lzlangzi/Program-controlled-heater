#ifndef  __DELAY_H
#define  __DELAY_H
#include "stm8s.h"

void Delay_Init(u8 clk); //��ʱ������ʼ��
void Delay_us(u16 nus);  //us����ʱ����,���65536us.
void Delay_ms(u32 nms);  //ms����ʱ����
#endif
