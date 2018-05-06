#ifndef _DS1302_H_
#define _DS1302_H_


/*******************************************************************************/
#define DS1302_SCLK         GPIO_PIN_0 //SCLK
#define DS1302_SDA          GPIO_PIN_1 //SDA
#define DS1302_RST          GPIO_PIN_2 //CE
#define GPIO_DS1302         GPIOB      //定义要使用的端口A
/**********************************************************/
#define DS1302_RST_OUT()    GPIO_Init(GPIO_DS1302, DS1302_RST, GPIO_MODE_OUT_PP_HIGH_SLOW)
#define DS1302_SCLK_OUT()   GPIO_Init(GPIO_DS1302, DS1302_SCLK, GPIO_MODE_OUT_PP_HIGH_SLOW)
#define DS1302_SDA_OUT()    GPIO_Init(GPIO_DS1302, DS1302_SDA, GPIO_MODE_OUT_PP_HIGH_SLOW)//高速推挽输出高电平
#define DS1302_SDA_IN()     GPIO_Init(GPIO_DS1302, DS1302_SDA, GPIO_MODE_IN_PU_NO_IT)//上拉输入
/**********************************************************/
#define DS1302_RST_H()      GPIO_WriteHigh(GPIO_DS1302, DS1302_RST)
#define DS1302_RST_L()      GPIO_WriteLow(GPIO_DS1302, DS1302_RST)

#define DS1302_SCLK_H()     GPIO_WriteHigh(GPIO_DS1302, DS1302_SCLK)
#define DS1302_SCLK_L()     GPIO_WriteLow(GPIO_DS1302, DS1302_SCLK)

#define DS1302_SDA_H()      GPIO_WriteHigh(GPIO_DS1302, DS1302_SDA)
#define DS1302_SDA_L()      GPIO_WriteLow(GPIO_DS1302, DS1302_SDA)
#define DS1302_DATA_IN()    GPIO_ReadInputPin(GPIO_DS1302,DS1302_SDA)
/**********************************************************/
//DS1302地址定义
#define ds1302_sec_add          0x80                //秒数据地址
#define ds1302_min_add          0x82                //分数据地址
#define ds1302_hr_add           0x84                //时数据地址
#define ds1302_date_add         0x86                //日数据地址
#define ds1302_month_add        0x88                //月数据地址
#define ds1302_day_add          0x8a                //星期数据地址
#define ds1302_year_add         0x8c                //年数据地址
#define ds1302_control_add      0x8e                //控制数据地址
#define ds1302_charger_add      0x90                                          
#define ds1302_clkburst_add     0xbe
/**********************************************************/

extern void DS1302_Init(void);
extern void DS1302_Write_Byte(u8 addr, u8 data);
extern u8   DS1302_Read_Byte(u8 addr);
extern void DS1302_Write_Time(void);
extern void DS1302_Read_Time(void);
extern void DS1302_Get_Time(u8 *time);

/**********************************************************/
#endif 
