#include "include.h"

void P_time()
{

    u8 time[16], SendBuf3[50];
    
    DS1302_Get_Time(time);                  //从ds1302获取时间
    sprintf(SendBuf3,"%d%d%d%d-%d%d-%d%d time%d%d:%d%d:%d%d week%d ",time[0],time[1],time[2],time[3],time[4],time[5],time[6],time[7],time[9],time[10],time[11],time[12],time[13],time[14],time[8]);  
    Send_Str(SendBuf3);
    Send_Str("\r\n");


}