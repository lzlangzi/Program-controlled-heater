#include "stm8s.h"
#include "ds18b20.h"

/*******************************************************************************
* 函 数 名         : Ds18b20Init
* 函数功能		   : 初始化
* 输    入         : 无
* 输    出         : 初始化成功返回1，失败返回0
*******************************************************************************/

u8 Ds18b20Init()
{
	u8 i;
        GPIO_DeInit(GPIOA);
        
        GPIO_WriteLow(GPIOA, GPIO_PIN_1);
        Delay_us(600);
        
        GPIO_WriteHigh(GPIOA, GPIO_PIN_1);
        Delay_us(10);                                //然后拉高总线，如果DS18B20做出反应会将在15us~60us后总线拉低
	GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);
        
        
	while(GPIO_ReadInputPin(GPIOA, GPIO_PIN_1)) //等待DS18B20拉低总线

          
	{
		Delay_ms(1);
		i++;
		if(i>5)//等待>5MS
		{
			return 0;//初始化失败
		}
	
	}
        
        return 1;//初始化成功
}

/*******************************************************************************
* 函 数 名         : Ds18b20WriteByte
* 函数功能		   : 向18B20写入一个字节
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Ds18b20WriteByte(u8 dat)
{
	u16 j;
        GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_FAST);

	for(j=0; j<8; j++)
	{
                GPIO_WriteLow(GPIOA, GPIO_PIN_1);

                Delay_us(1);

		if((dat&0x01))
                {
                    GPIO_WriteHigh(GPIOA, GPIO_PIN_1);
                }
                else 
                {
                    GPIO_WriteLow(GPIOA, GPIO_PIN_1);
                }
                dat >>= 1;

                Delay_us(60);
		GPIO_WriteHigh(GPIOA, GPIO_PIN_1);

		Delay_us(1);
                
	}
}
/*******************************************************************************
* 函 数 名         : Ds18b20ReadByte
* 函数功能		   : 读取一个字节
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/


u8 Ds18b20ReadByte()
{
	u8 byte, bi;
	u16  j;	
        
	for(j=8; j>0; j--)
	{
                GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_FAST);
		//先将总线拉低1us
		GPIO_WriteLow(GPIOA, GPIO_PIN_1);
                Delay_us(1);
                
		GPIO_WriteHigh(GPIOA, GPIO_PIN_1);//然后释放总线
		Delay_us(6);
		//延时6us等待数据稳定
                GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);
		if(GPIO_ReadInputPin(GPIOA, GPIO_PIN_1))
                
                {
                    bi = 0x01;
                }  //读取数据，从最低位开始读取
		
                else bi = 0x00;
                /*将byte左移一位，然后与上右移7位后的bi，注意移动之后移掉那位补0。*/
		byte = (byte >> 1) | (bi << 7);	
                Delay_us(60);
                
	}				
	return byte;
}
/*******************************************************************************
* 函 数 名         : Ds18b20ChangTemp
* 函数功能		   : 让18b20开始转换温度
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void  Ds18b20ChangTemp()
{
	Ds18b20Init();
	Delay_ms(1);
	Ds18b20WriteByte(0xcc);		//跳过ROM操作命令		 
	Ds18b20WriteByte(0x44);	    //温度转换命令
	
   
}
/*******************************************************************************
* 函 数 名         : Ds18b20ReadTempCom
* 函数功能		   : 发送读取温度命令
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void  Ds18b20ReadTempCom()
{	

	Ds18b20Init();
	Delay_ms(1);
	Ds18b20WriteByte(0xcc);	 //跳过ROM操作命令
	Ds18b20WriteByte(0xbe);	 //发送读取温度命令
}
/*******************************************************************************
* 函 数 名         : Ds18b20ReadTemp
* 函数功能		   : 读取温度
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

int Ds18b20ReadTemp()
{
	int temp = 0;
	u8 tmh, tml;
	Ds18b20ChangTemp();			 	//先写入转换命令
	Ds18b20ReadTempCom();			//然后等待转换完后发送读取温度命令
	tml = Ds18b20ReadByte();		//读取温度值共16位，先读低字节
	tmh = Ds18b20ReadByte();		//再读高字节
	temp = tmh;
	temp <<= 8;
	temp |= tml;
	return temp;
}



