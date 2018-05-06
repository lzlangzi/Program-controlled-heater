#include"include.h"

/*****************************************************************************
****全局变量
*****************************************************************************/
 unsigned char DHT11_Value[6] = {0,0,0,0,0};

/*****************************************************************************
****函数功能：DHT11读取一个字节的数据
****输入参数：无
****输出参数：一个字节的数据
*****************************************************************************/
unsigned char DHT11_ReadOneByte(void)
{
    unsigned char  value = 0, i = 0, temp = 0;
    for(i = 0; i < 8; i++)
    {
        temp = 0;          //先赋值为0
        while( !(GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS)) );    //等待进入高电平
        Delay_us(30);         //等待30us，若是信号'0'，则会为低电平
        if( (GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS)) )   //高电平进入，此时信号为'1'
        {
            temp = 1;        //赋值为1
            //Delay_us(40);
            while( GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS) );
        }
        value <<= 1;             //value值向左移位
        value |= temp;           //将temp值赋值到value上
    }
    return value;
}

/*****************************************************************************
****函数功能：读温度湿度函数
****输入参数：无
****输出参数：
*****************************************************************************/
unsigned char DHT11_ReadData(void)
{
    unsigned char i = 0,  check_value = 0;
    GPIO_Init(DHT11_DATA_PORT, (GPIO_Pin_TypeDef)DHT11_DATA_PINS, GPIO_MODE_OUT_PP_HIGH_FAST); //切换为推挽输出
    GPIO_WriteLow(DHT11_DATA_PORT, DHT11_DATA_PINS);      //低电平
    Delay_ms(20);                                         //等待大于18ms
    GPIO_WriteHigh(DHT11_DATA_PORT, DHT11_DATA_PINS);     //释放数据线，用于检测低电平的应答信号
    Delay_us(30);                                         //延时40us
    GPIO_Init(DHT11_DATA_PORT, (GPIO_Pin_TypeDef)DHT11_DATA_PINS, GPIO_MODE_IN_FL_NO_IT);  //切换为上拉输入模式
    while( !GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS) ); //检测是否为低电平
    //有应答信号
    while( GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS)); //等待应答信号结束
        
    //读出温湿度值
    for(i = 0; i < SIZE; i++)
    {
        DHT11_Value[i] = DHT11_ReadOneByte();
    }
        
    for(i = 0; i < SIZE - 1; i++)        //将前四个字节值相加，等待校验
    {
        check_value += DHT11_Value[i];
    } 
        
    //进行校验
    if(check_value == DHT11_Value[SIZE - 1])   //校验正确
    {
        return OK;
    }
    else                                       //校验出错
    {
        return ERROR;
    }
}