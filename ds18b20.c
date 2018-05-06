#include "stm8s.h"
#include "ds18b20.h"

/*******************************************************************************
* �� �� ��         : Ds18b20Init
* ��������		   : ��ʼ��
* ��    ��         : ��
* ��    ��         : ��ʼ���ɹ�����1��ʧ�ܷ���0
*******************************************************************************/

u8 Ds18b20Init()
{
	u8 i;
        GPIO_DeInit(GPIOA);
        
        GPIO_WriteLow(GPIOA, GPIO_PIN_1);
        Delay_us(600);
        
        GPIO_WriteHigh(GPIOA, GPIO_PIN_1);
        Delay_us(10);                                //Ȼ���������ߣ����DS18B20������Ӧ�Ὣ��15us~60us����������
	GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);
        
        
	while(GPIO_ReadInputPin(GPIOA, GPIO_PIN_1)) //�ȴ�DS18B20��������

          
	{
		Delay_ms(1);
		i++;
		if(i>5)//�ȴ�>5MS
		{
			return 0;//��ʼ��ʧ��
		}
	
	}
        
        return 1;//��ʼ���ɹ�
}

/*******************************************************************************
* �� �� ��         : Ds18b20WriteByte
* ��������		   : ��18B20д��һ���ֽ�
* ��    ��         : ��
* ��    ��         : ��
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
* �� �� ��         : Ds18b20ReadByte
* ��������		   : ��ȡһ���ֽ�
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/


u8 Ds18b20ReadByte()
{
	u8 byte, bi;
	u16  j;	
        
	for(j=8; j>0; j--)
	{
                GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_FAST);
		//�Ƚ���������1us
		GPIO_WriteLow(GPIOA, GPIO_PIN_1);
                Delay_us(1);
                
		GPIO_WriteHigh(GPIOA, GPIO_PIN_1);//Ȼ���ͷ�����
		Delay_us(6);
		//��ʱ6us�ȴ������ȶ�
                GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);
		if(GPIO_ReadInputPin(GPIOA, GPIO_PIN_1))
                
                {
                    bi = 0x01;
                }  //��ȡ���ݣ������λ��ʼ��ȡ
		
                else bi = 0x00;
                /*��byte����һλ��Ȼ����������7λ���bi��ע���ƶ�֮���Ƶ���λ��0��*/
		byte = (byte >> 1) | (bi << 7);	
                Delay_us(60);
                
	}				
	return byte;
}
/*******************************************************************************
* �� �� ��         : Ds18b20ChangTemp
* ��������		   : ��18b20��ʼת���¶�
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void  Ds18b20ChangTemp()
{
	Ds18b20Init();
	Delay_ms(1);
	Ds18b20WriteByte(0xcc);		//����ROM��������		 
	Ds18b20WriteByte(0x44);	    //�¶�ת������
	
   
}
/*******************************************************************************
* �� �� ��         : Ds18b20ReadTempCom
* ��������		   : ���Ͷ�ȡ�¶�����
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void  Ds18b20ReadTempCom()
{	

	Ds18b20Init();
	Delay_ms(1);
	Ds18b20WriteByte(0xcc);	 //����ROM��������
	Ds18b20WriteByte(0xbe);	 //���Ͷ�ȡ�¶�����
}
/*******************************************************************************
* �� �� ��         : Ds18b20ReadTemp
* ��������		   : ��ȡ�¶�
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

int Ds18b20ReadTemp()
{
	int temp = 0;
	u8 tmh, tml;
	Ds18b20ChangTemp();			 	//��д��ת������
	Ds18b20ReadTempCom();			//Ȼ��ȴ�ת������Ͷ�ȡ�¶�����
	tml = Ds18b20ReadByte();		//��ȡ�¶�ֵ��16λ���ȶ����ֽ�
	tmh = Ds18b20ReadByte();		//�ٶ����ֽ�
	temp = tmh;
	temp <<= 8;
	temp |= tml;
	return temp;
}



