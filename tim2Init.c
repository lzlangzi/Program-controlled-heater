#include"include.h"
/*****************************************************************************
  * @function  : Tim2_Init
  * @brief     : TIM2��ʼ������ CH2,3������LED�ĺ����仯��
  * @note      : STM8S105K
  * @param     : null
  * @retval    : null
             
******************************************************************************/
void Tim2_Init(void)                    //TIM2�ĳ�ʼ�������
{
//         //����ͨ��1
//         TIM2_TimeBaseInit(TIM2_PRESCALER_8, 1999);              //��һ������ʱ����Ԫ��������Ԥ��ƵPSCRH/L�ߵͰ�λ �Ĵ������������Զ�װ�ؼĴ���ARRH/L��
//         TIM2_OC1Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,0,TIM2_OCPOLARITY_LOW);                      //Ȼ������ͨ�������ģʽΪPWM����������Ƚϣ�ռ�ձ�����Ϊ0�����Ϊ�͵�ƽ
//         TIM2_OC1PreloadConfig(ENABLE);
//         TIM2_Cmd(ENABLE); 
//
//
//         //����ͨ��2
//         TIM2_TimeBaseInit(TIM2_PRESCALER_8, 1999);              //��һ������ʱ����Ԫ��������Ԥ��ƵPSCRH/L�ߵͰ�λ �Ĵ������������Զ�װ�ؼĴ���ARRH/L��
//         TIM2_OC2Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_HIGH);                      //Ȼ������ͨ�������ģʽΪPWM����������Ƚϣ�ռ�ձ�����Ϊ0�����Ϊ���͵�ƽ��
//         TIM2_OC2PreloadConfig(ENABLE);                          //����Ԥװ�ؼĴ���
//         TIM2_Cmd(ENABLE);                                       //���Ŀ���  ���ö�ʱ��



        //����ͨ��3
        TIM2_TimeBaseInit(TIM2_PRESCALER_8, 1999);            //��һ������ʱ����Ԫ��������Ԥ��ƵPSCRH/L�ߵͰ�λ �Ĵ������������Զ�װ�ؼĴ���ARRH/L��
        TIM2_OC3Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_HIGH);                      //Ȼ������ͨ�������ģʽΪPWM����������Ƚϣ�ռ�ձ�����Ϊ0�����Ϊ�͵�ƽ
        TIM2_OC3PreloadConfig(ENABLE);
        TIM2_Cmd(ENABLE); 

}
/*****************************************************************************
  * @function  : Delay
  * @brief     : ��ʱ
  * @note      : STM8S105K
  * @param     : null
  * @retval    : null
             
******************************************************************************/
void Delay(unsigned int time)
{
    while(time--);
}
