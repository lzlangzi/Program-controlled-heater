#include"include.h"





//u8 time_buf[8] = {0x20,0x18,0x03,0x20,0x23,0x53,0x55,0x03}; //初始时间2018年3月20号23点59分55秒 星期三
u8 READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
u8 WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
u8 TIME[7] = {0, 0, 0x12, 0x01, 0x01, 0x07, 0x17};
//---存储顺序是秒分时日月周年,存储格式是用BCD码---//
void DS1302_Init(void)                                     //DS1302初始化
{
    DS1302_RST_OUT();
    DS1302_SCLK_OUT();
    DS1302_SDA_OUT();

}

void DS1302_Write_Byte(u8 addr, u8 data)                  //向DS1302写入一个字节数据
{
    u8 i;
    DS1302_Init();
    
    DS1302_RST_L();
    Delay_us(10);

    DS1302_SCLK_L();
    Delay_us(10);
    
    DS1302_RST_H();
    Delay_us(10);

    DS1302_SDA_H();
    Delay_us(10);
   // addr= addr&0xFE;                                     //最低位置零，写数据
    DS1302_SDA_OUT();                                    //写地址、数据
    Delay_us(10);
    for(i=8;i>0;i--)
    {
      if(addr&0x01)
        DS1302_SDA_H();
      else
        DS1302_SDA_L();
      addr=addr>>1;
      Delay_us(10);
      DS1302_SCLK_H();                                   //产生时钟
      Delay_us(10);
      DS1302_SCLK_L();
      Delay_us(10);
    }
    for(i=8;i>0;i--)
    {
      if(data&0x01)
        DS1302_SDA_H();
      else
        DS1302_SDA_L();
      Delay_us(10);
      data=data>>1;
      DS1302_SCLK_H();
      Delay_us(10);
      DS1302_SCLK_L();
      Delay_us(10);
    }
    DS1302_RST_L();//停止DS1302总线
    Delay_us(10);
}

u8 DS1302_Read_Byte(u8 addr)
{
    u8 i,temp = 0;
    u8 dat, dat1;
    DS1302_RST_L();
    Delay_us(10);
    DS1302_SCLK_L();
    Delay_us(10);
    DS1302_RST_H();
 //   addr= addr|0x01;                       //最低位置高，读数据
    DS1302_SDA_OUT();                      //写地址
    Delay_us(10);
    for(i=8;i>0;i--)
    {
       
      
      if(addr&0x01)
        DS1302_SDA_H();                     //时数r
      else
        DS1302_SDA_L();
      addr=addr>>1;
      DS1302_SCLK_H();                     //产生时钟  !
      Delay_us(10);
      DS1302_SCLK_L();                     //产生时钟
      Delay_us(10);

      
    }
    Delay_us(10);
    DS1302_SDA_IN();                      //读数据
    Delay_us(10);
    for(i=8;i>0;i--)
    {
      temp = temp >> 1;
      if(DS1302_DATA_IN())
        temp |= 0x80;
      else
        temp &= 0x7F;
      DS1302_SCLK_H();
      Delay_us(10);
      DS1302_SCLK_L();
//        dat1 = DS1302_DATA_IN();
//        Delay_us(10);
//        dat = (dat>>1)|(dat1<<7);
//        DS1302_SCLK_H();
//        Delay_us(15);
//        DS1302_SCLK_L();
//        Delay_us(15);
    }
    DS1302_RST_L();//停止DS1302总线
    Delay_us(10);
    DS1302_SCLK_H();
    Delay_us(10);
    DS1302_SDA_L();
    Delay_us(10);
    DS1302_SDA_H();
    Delay_us(10);
    DS1302_SDA_OUT();//读取字节之前，将IO设置为输入口，读取完之后，要将其改回输出口
    return temp;
}

void DS1302_Write_Time(void)//向DS1302写入时间数据
{
//    DS1302_Write_Byte(0x8E, 0x00);       //关闭写保护
//    //DS1302_Write_Byte(ds1302_sec_add, 0x80);         //暂停时钟
//    DS1302_Write_Byte(ds1302_charger_add, 0xA9);     //涓流充电
//    DS1302_Write_Byte(ds1302_year_add, time_buf[1]);    //年 
//    DS1302_Write_Byte(ds1302_month_add,time_buf[2]);   //月 
//    DS1302_Write_Byte(ds1302_date_add, time_buf[3]);    //日 
//    DS1302_Write_Byte(ds1302_hr_add,   time_buf[4]);      //时 
//    DS1302_Write_Byte(ds1302_min_add,  time_buf[5]);     //分
//    DS1302_Write_Byte(ds1302_sec_add,  time_buf[6]);     //秒
//    DS1302_Write_Byte(ds1302_day_add,  time_buf[7]);     //周 
//    DS1302_Write_Byte(0x8E,0x80);        //打开写保护 
      u8 n;
      DS1302_Write_Byte(0x8E, 0x00);       //关闭写保护
      for (n=0; n<7; n++)//写入7个字节的时钟信号：分秒时日月周年
	{
		DS1302_Write_Byte(WRITE_RTC_ADDR[n],TIME[n]);	
	}
      DS1302_Write_Byte(0x8E,0x80);        //打开写保护
}

void DS1302_Read_Time(void)//从DS302读出时钟数据  
{
//    time_buf[1] = DS1302_Read_Byte(0x8d);                     //年 
//    time_buf[2] = DS1302_Read_Byte(0x89);                     //月 
//    time_buf[3] = DS1302_Read_Byte(0x87);                     //日 
//    time_buf[4] = DS1302_Read_Byte(0x85);                     //时 
//    time_buf[5] = DS1302_Read_Byte(0x83);                     //分 
//    time_buf[6] = (DS1302_Read_Byte(0x81))&0x7f;              //秒，屏蔽秒的第7位，避免超出59
//    time_buf[7] = DS1302_Read_Byte(0x8b);                     //周         

      	u16 n;
	for (n=0; n<7; n++)//读取7个字节的时钟信号：分秒时日月周年
	{
		TIME[n] = DS1302_Read_Byte(READ_RTC_ADDR[n]);
	}
}


void DS1302_Get_Time(u8 *time)//DS1302向上层返回时间数据
{
    DS1302_Read_Time();
    time[0]=2;   //年   
    time[1]=0;
     
    time[2]=(TIME[6]/16);   
    time[3]=(TIME[6]&0x0f);
    
    time[4]=(TIME[4]/16);   //月  
    time[5]=(TIME[4]&0x0f);

    time[6]=(TIME[3]/16);   //日   
    time[7]=(TIME[3]&0x0f);
     
    time[8]=(TIME[5]&0x07); //星期
     
    time[9]=(TIME[2]/16);   //时   
    time[10]=(TIME[2]&0x0f);   

    time[11]=(TIME[1]/16);  //分   
    time[12]=(TIME[1]&0x0f);   

    time[13]=(TIME[0]/16);  //秒
    time[14]=(TIME[0]&0x0f);
}


