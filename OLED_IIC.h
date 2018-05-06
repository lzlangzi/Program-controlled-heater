#ifndef _OLED_IIC_H_
#define _OLED_IIC_H_


#include "stm8s.h"
#include "clock.h"
#include "stdio.h"



/**********************************************************************************
****宏定义
**********************************************************************************/
#define IIC_SCL_PORT  (GPIOB)
#define IIC_SCL_PINS  (GPIO_PIN_4)

#define IIC_SDA_PORT  (GPIOB)
#define IIC_SDA_PINS  (GPIO_PIN_5)

#define high 1
#define low 0

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

extern u16 TempData[6], p, speed;
extern float temperature_read, temperature;
extern float E;
extern float temp;
extern u16 pwm;


/**********************************************************************************
****函数声明
**********************************************************************************/
 void delay(unsigned int z);
 void GPIO_IIC_Start();
 void GPIO_IIC_Stop();
 void GPIO_IIC_SendOneByte(unsigned char IIC_Byte);
 void OLED_WriteDat(unsigned char IIC_Data);
 void OLED_WriteCmd(unsigned char IIC_Command);
 void OLED_SetPos(unsigned char x, unsigned char y);
 void OLED_Fill(unsigned char FillData);
 void OLED_CS(void);
 void OLED_Init(void);
 void OLED_P6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);
 void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
 void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned char N);
 void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,const unsigned char BMP[]);

#endif
