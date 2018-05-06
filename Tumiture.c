#include "include.h"

void Tumiture()
{
    u8 SendBuf2[30];
    GPIO_DeInit(GPIOF);          //��ʼ��DHT11��Ӧgpio
    while(!DHT11_ReadData());
    
    sprintf(SendBuf2,"Temp:%c%c%Humi:%c%c% \r\n\n\0",DHT11_Value[0]/10+'0',DHT11_Value[0]%10+'0',DHT11_Value[2]/10+'0',DHT11_Value[2]%10+'0');
    Send_Str(SendBuf2);    //���͵�����
    Send_Str("\r\n");
    Delay_ms(2000);

}