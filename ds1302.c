#include"include.h"





//u8 time_buf[8] = {0x20,0x18,0x03,0x20,0x23,0x53,0x55,0x03}; //��ʼʱ��2018��3��20��23��59��55�� ������
u8 READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
u8 WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
u8 TIME[7] = {0, 0, 0x12, 0x01, 0x01, 0x07, 0x17};
//---�洢˳�������ʱ��������,�洢��ʽ����BCD��---//
void DS1302_Init(void)                                     //DS1302��ʼ��
{
    DS1302_RST_OUT();
    DS1302_SCLK_OUT();
    DS1302_SDA_OUT();

}

void DS1302_Write_Byte(u8 addr, u8 data)                  //��DS1302д��һ���ֽ�����
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
   // addr= addr&0xFE;                                     //���λ���㣬д����
    DS1302_SDA_OUT();                                    //д��ַ������
    Delay_us(10);
    for(i=8;i>0;i--)
    {
      if(addr&0x01)
        DS1302_SDA_H();
      else
        DS1302_SDA_L();
      addr=addr>>1;
      Delay_us(10);
      DS1302_SCLK_H();                                   //����ʱ��
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
    DS1302_RST_L();//ֹͣDS1302����
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
 //   addr= addr|0x01;                       //���λ�øߣ�������
    DS1302_SDA_OUT();                      //д��ַ
    Delay_us(10);
    for(i=8;i>0;i--)
    {
       
      
      if(addr&0x01)
        DS1302_SDA_H();                     //ʱ��r
      else
        DS1302_SDA_L();
      addr=addr>>1;
      DS1302_SCLK_H();                     //����ʱ��  !
      Delay_us(10);
      DS1302_SCLK_L();                     //����ʱ��
      Delay_us(10);

      
    }
    Delay_us(10);
    DS1302_SDA_IN();                      //������
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
    DS1302_RST_L();//ֹͣDS1302����
    Delay_us(10);
    DS1302_SCLK_H();
    Delay_us(10);
    DS1302_SDA_L();
    Delay_us(10);
    DS1302_SDA_H();
    Delay_us(10);
    DS1302_SDA_OUT();//��ȡ�ֽ�֮ǰ����IO����Ϊ����ڣ���ȡ��֮��Ҫ����Ļ������
    return temp;
}

void DS1302_Write_Time(void)//��DS1302д��ʱ������
{
//    DS1302_Write_Byte(0x8E, 0x00);       //�ر�д����
//    //DS1302_Write_Byte(ds1302_sec_add, 0x80);         //��ͣʱ��
//    DS1302_Write_Byte(ds1302_charger_add, 0xA9);     //������
//    DS1302_Write_Byte(ds1302_year_add, time_buf[1]);    //�� 
//    DS1302_Write_Byte(ds1302_month_add,time_buf[2]);   //�� 
//    DS1302_Write_Byte(ds1302_date_add, time_buf[3]);    //�� 
//    DS1302_Write_Byte(ds1302_hr_add,   time_buf[4]);      //ʱ 
//    DS1302_Write_Byte(ds1302_min_add,  time_buf[5]);     //��
//    DS1302_Write_Byte(ds1302_sec_add,  time_buf[6]);     //��
//    DS1302_Write_Byte(ds1302_day_add,  time_buf[7]);     //�� 
//    DS1302_Write_Byte(0x8E,0x80);        //��д���� 
      u8 n;
      DS1302_Write_Byte(0x8E, 0x00);       //�ر�д����
      for (n=0; n<7; n++)//д��7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		DS1302_Write_Byte(WRITE_RTC_ADDR[n],TIME[n]);	
	}
      DS1302_Write_Byte(0x8E,0x80);        //��д����
}

void DS1302_Read_Time(void)//��DS302����ʱ������  
{
//    time_buf[1] = DS1302_Read_Byte(0x8d);                     //�� 
//    time_buf[2] = DS1302_Read_Byte(0x89);                     //�� 
//    time_buf[3] = DS1302_Read_Byte(0x87);                     //�� 
//    time_buf[4] = DS1302_Read_Byte(0x85);                     //ʱ 
//    time_buf[5] = DS1302_Read_Byte(0x83);                     //�� 
//    time_buf[6] = (DS1302_Read_Byte(0x81))&0x7f;              //�룬������ĵ�7λ�����ⳬ��59
//    time_buf[7] = DS1302_Read_Byte(0x8b);                     //��         

      	u16 n;
	for (n=0; n<7; n++)//��ȡ7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		TIME[n] = DS1302_Read_Byte(READ_RTC_ADDR[n]);
	}
}


void DS1302_Get_Time(u8 *time)//DS1302���ϲ㷵��ʱ������
{
    DS1302_Read_Time();
    time[0]=2;   //��   
    time[1]=0;
     
    time[2]=(TIME[6]/16);   
    time[3]=(TIME[6]&0x0f);
    
    time[4]=(TIME[4]/16);   //��  
    time[5]=(TIME[4]&0x0f);

    time[6]=(TIME[3]/16);   //��   
    time[7]=(TIME[3]&0x0f);
     
    time[8]=(TIME[5]&0x07); //����
     
    time[9]=(TIME[2]/16);   //ʱ   
    time[10]=(TIME[2]&0x0f);   

    time[11]=(TIME[1]/16);  //��   
    time[12]=(TIME[1]&0x0f);   

    time[13]=(TIME[0]/16);  //��
    time[14]=(TIME[0]&0x0f);
}


