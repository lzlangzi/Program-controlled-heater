#ifndef _DHT11_h_
#define _DHT11_h_

/********************************************************************************
****宏定义
********************************************************************************/
#define  DHT11_DATA_PORT  (GPIOF)
#define  DHT11_DATA_PINS  (GPIO_PIN_4)

#define  OK      1
#define  ERROR   0
#define  SIZE    5

/********************************************************************************
****函数声明
********************************************************************************/
extern unsigned char DHT11_ReadOneByte(void);
extern unsigned char DHT11_ReadData(void);
extern unsigned char DHT11_Value[6];

#endif