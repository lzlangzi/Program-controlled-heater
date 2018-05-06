#include"include.h"

/*****************************************************************************
****ȫ�ֱ���
*****************************************************************************/
 unsigned char DHT11_Value[6] = {0,0,0,0,0};

/*****************************************************************************
****�������ܣ�DHT11��ȡһ���ֽڵ�����
****�����������
****���������һ���ֽڵ�����
*****************************************************************************/
unsigned char DHT11_ReadOneByte(void)
{
    unsigned char  value = 0, i = 0, temp = 0;
    for(i = 0; i < 8; i++)
    {
        temp = 0;          //�ȸ�ֵΪ0
        while( !(GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS)) );    //�ȴ�����ߵ�ƽ
        Delay_us(30);         //�ȴ�30us�������ź�'0'�����Ϊ�͵�ƽ
        if( (GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS)) )   //�ߵ�ƽ���룬��ʱ�ź�Ϊ'1'
        {
            temp = 1;        //��ֵΪ1
            //Delay_us(40);
            while( GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS) );
        }
        value <<= 1;             //valueֵ������λ
        value |= temp;           //��tempֵ��ֵ��value��
    }
    return value;
}

/*****************************************************************************
****�������ܣ����¶�ʪ�Ⱥ���
****�����������
****���������
*****************************************************************************/
unsigned char DHT11_ReadData(void)
{
    unsigned char i = 0,  check_value = 0;
    GPIO_Init(DHT11_DATA_PORT, (GPIO_Pin_TypeDef)DHT11_DATA_PINS, GPIO_MODE_OUT_PP_HIGH_FAST); //�л�Ϊ�������
    GPIO_WriteLow(DHT11_DATA_PORT, DHT11_DATA_PINS);      //�͵�ƽ
    Delay_ms(20);                                         //�ȴ�����18ms
    GPIO_WriteHigh(DHT11_DATA_PORT, DHT11_DATA_PINS);     //�ͷ������ߣ����ڼ��͵�ƽ��Ӧ���ź�
    Delay_us(30);                                         //��ʱ40us
    GPIO_Init(DHT11_DATA_PORT, (GPIO_Pin_TypeDef)DHT11_DATA_PINS, GPIO_MODE_IN_FL_NO_IT);  //�л�Ϊ��������ģʽ
    while( !GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS) ); //����Ƿ�Ϊ�͵�ƽ
    //��Ӧ���ź�
    while( GPIO_ReadInputPin(DHT11_DATA_PORT, DHT11_DATA_PINS)); //�ȴ�Ӧ���źŽ���
        
    //������ʪ��ֵ
    for(i = 0; i < SIZE; i++)
    {
        DHT11_Value[i] = DHT11_ReadOneByte();
    }
        
    for(i = 0; i < SIZE - 1; i++)        //��ǰ�ĸ��ֽ�ֵ��ӣ��ȴ�У��
    {
        check_value += DHT11_Value[i];
    } 
        
    //����У��
    if(check_value == DHT11_Value[SIZE - 1])   //У����ȷ
    {
        return OK;
    }
    else                                       //У�����
    {
        return ERROR;
    }
}