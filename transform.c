#include "transform.h"
char ch1[8], ch2[8];
/*******************************************************************************
* 函 数 名       : Transform
* 函数功能       : 数字字符转化
* 输    入       : 无
* 输    出    	 : 无
* 备    注	 : 
*******************************************************************************/
unsigned char* Transform(unsigned int num)
{
    int i = 0, j = 0;

    if(num)
    {
        while(num)
        {
            ch1[i] = num%10+'0';
            num /= 10;
            i++;
        }
        ch2[i]='\0';
        for(i=i-1; i>=0; i--)
        {
            ch2[j] = ch1[i];
            j++;
        }
        return ch2;
    }
      
    else 
    {
        ch2[0]=num+'0';
        ch2[1]='\0';
        
    }return ch2;
    
 
}