#include "include.h"

volatile u8 fac_us=0; //us延时倍乘数  

/*****************************************************
*函数名：Delay_Init
*函数功能：延时函数初始化
*输入：时钟频率
*输出：无
*备注：无
*****************************************************/
void Delay_Init(u8 clk)
{
 if(clk>16)fac_us = (16-4)/4;//24Mhz时,stm8大概19个周期为1us
 else if(clk>4)fac_us = (clk-4)/4; 
 else fac_us = 1;
}
//延时nus
//


/*****************************************************
*函数名：Delay_us
*函数功能：延时us
*输入：时间
*输出：无
*备注：延时时间=(fac_us*4+4)*nus*(T)
//其中,T为CPU运行频率(Mhz)的倒数,单位为us.
//准确度:
   92%  @24Mhz
   98%  @16Mhz
   98%  @12Mhz
   86%  @8Mhz
*****************************************************/
void Delay_us(u16 nus)
{  
  __asm(
  "PUSH A          \n"  //1T,压栈
  "DELAY_XUS:      \n"   
  "LD A,fac_us     \n"   //1T,fac_us加载到累加器A
  "DELAY_US_1:     \n"  
  "NOP             \n"  //1T,nop延时
  "DEC A           \n"  //1T,A--
  "JRNE DELAY_US_1 \n"   //不等于0,则跳转(2T)到DELAY_US_1继续执行,若等于0,则不跳转(1T).
  "NOP             \n"  //1T,nop延时
  "DECW X          \n"  //1T,x--
  "JRNE DELAY_XUS  \n"    //不等于0,则跳转(2T)到DELAY_XUS继续执行,若等于0,则不跳转(1T).
  "POP A           \n"  //1T,出栈
  ); 
}

/*****************************************************
*函数名：Delay_ms
*函数功能：延时ms
*输入：时间
*输出：无
*备注：为保证准确度,nms不要大于16640.
*****************************************************/
void Delay_ms(u32 nms)
{
 u8 t;
 if(nms > 65)
 {
  t = nms / 65;
  while(t--) Delay_us(65000);
  nms = nms % 65;
 }
 Delay_us(nms * 1000);
}
