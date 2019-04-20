#include "PWM.h"
#include "Port.h"
void PWM1_Duty(unsigned char Duty)
{
	if(Duty==0)
			CCAP0H = CCAP0L = 0;
	else
	{
		unsigned char Temp=0xff-(2.55*Duty)/1;
		CCAP0H = CCAP0L = Temp;
	}
}
void PWM2_Duty(unsigned char Duty)
{
	if(Duty==0)
			CCAP1H = CCAP1L = 0;
	else
	{
		unsigned char Temp=0xff-(2.55*Duty)/1;
		CCAP1H = CCAP1L = Temp;
	}
}
void Init_PWM()
{    
    CCON = 0;                       //�����־λ
    CL = 0;                         //����PCA����ʱ��
    CH = 0;													//����PCA����ʱ��
    CMOD = 0x02;                    //����ʱ��Ƶ������Ƶ�Ķ���֮һ                           
    CCAP0H = CCAP0L = 0xff;         //����PWM0��ռ�ձ�Ϊ100%
    CCAPM0 = 0x42;                  //PCA0������8λģʽ��ֵ��Ϊ(0x00~0xff)����ѯģʽ
    CCAP1H = CCAP1L = 0xff;         //����PWM1��ռ�ձ�Ϊ100%
    CCAPM1 = 0x42;                  //PCA1������8λģʽ��ֵ��Ϊ(0x00~0xff)����ѯģʽ
    CR = 1;                         //PCA����
}