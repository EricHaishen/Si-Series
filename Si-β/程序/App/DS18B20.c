#include "DS18B20.h"
#include "stm32f10x_it.h"
#include "System.h"
/*******************************************************************************
* �� �� ��         : ds18b20_init
* ��������		   : IO�˿�ʱ�ӳ�ʼ������	   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Ds18b20_init()
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=DS18B20_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(DS18B20_Port,&GPIO_InitStructure);
}

/*******************************************************************************
* �� �� ��         : DQININT
* ��������		   : ��������	   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void DQININT()	 //��������
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=DS18B20_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(DS18B20_Port,&GPIO_InitStructure);	
}

/*******************************************************************************
* �� �� ��         : DQOUTINT
* ��������		   : �������	   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void DQOUTINT()	 //�������
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=DS18B20_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(DS18B20_Port,&GPIO_InitStructure);	
}

/*******************************************************************************
* �� �� ��         : ds18b20init
* ��������		   : DS18B20��ʼ��ʱ��	   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void ds18b20init()
{
	DQOUTINT();//���
	ds18b20_dq_L;
	Delayus(480);//��ʱ480΢��	
	ds18b20_dq_H;
	Delayus(480);//��ʱ480΢��
}

/*******************************************************************************
* �� �� ��         : ds18b20wr
* ��������		   : DS18B20д����ʱ��	   
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/
void ds18b20wr(unsigned char dat)
{
	u8 i=0;
	DQOUTINT();//���

	for(i=0;i<8;i++)
	{
		ds18b20_dq_L;	 //����
		Delayus(15);//��ʱ15΢��
		
		if((dat&0x01)==1)
		{
			ds18b20_dq_H;
		}
		else
		{
			ds18b20_dq_L;
		}
		Delayus(60);//��ʱ60΢��
		ds18b20_dq_H;
		
		dat>>=1;//׼����һλ���ݵķ���	
	}
}

/*******************************************************************************
* �� �� ��         : DS18b20rd
* ��������		   : DS18B20������ʱ��	   
* ��    ��         : ��
* ��    ��         : value
*******************************************************************************/
unsigned char DS18b20rd()
{
	u8 i=0,value=0;
	for(i=0;i<8;i++)
	{
		value>>=1;
		DQOUTINT();//���
		ds18b20_dq_L;	 //����
		Delayus(4);//��ʱ4΢��
		ds18b20_dq_H;
		Delayus(10);//��ʱ10΢��
		DQININT();	 //��������

		if(GPIO_ReadInputDataBit(DS18B20_Port,DS18B20_Pin)==1)
		{
		   value|=0x80;//������ �ӵ�λ��ʼ
		}
		Delayus(45);//��ʱ45΢��
	}
	return value;	
}

/*******************************************************************************
* �� �� ��         : readtemp
* ��������		   : DS18B2�¶ȼĴ������ã��¶ȶ�ȡ	   
* ��    ��         : ��
* ��    ��         : value
*******************************************************************************/
double readtemp()			  //��ȡ�¶�����Ҫ��λ��
{
	u16 temp;
	u8 a,b;
	double value;
	ds18b20init();		//��ʼ��
	ds18b20wr(0xcc);   //���ͺ���ROMָ��
	ds18b20wr(0x44);   //�����¶�ת��ָ��
	Delayms(500);
	ds18b20init();	   //��ʼ��
	ds18b20wr(0xcc);   //���ͺ���ROMָ��
	ds18b20wr(0xbe);   //�����ݴ���ָ��
	a=DS18b20rd();	 //�¶ȵĵͰ�λ
	b=DS18b20rd();	 //�¶ȵĸ߰�λ
	temp=b;
	temp=(temp<<8)+a;
	if((temp&0xf800)==0xf800)
	{
		temp=(~temp)+1;
		value=temp*(-0.0625);
	}
	else
	{
		value=temp*0.0625;	
	}
	return value;
}
