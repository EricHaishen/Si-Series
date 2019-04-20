#include "CPU_Temp.h"
#include "System.h"
void CPU_Temp_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M  ���14M ����ADCʱ�ӣ�ADCCLK��
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; 
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfChannel = 1; 
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);
	ADC_TempSensorVrefintCmd(ENABLE);//���ڲ��¶ȴ�����ʹ��
	ADC_Cmd(ADC1,ENABLE);	
	ADC_ResetCalibration(ADC1);//����ָ����ADC��У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//��ȡADC����У׼�Ĵ�����״̬
	ADC_StartCalibration(ADC1);//��ʼָ��ADC��У׼״̬
	while(ADC_GetCalibrationStatus(ADC1));//��ȡָ��ADC��У׼����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ�ܻ���ʧ��ָ����ADC�����ת����������
}
int Get_Temp(void)
{
	float ad;
	char i;
	u32 value;
	for(i=0;i<50;i++)	 //��ȡ50��AD����ٶȺ�����ƽ��ֵ
		{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//ת��������־λ
			value=value+ADC_GetConversionValue(ADC1);//�������һ��ADCx�������ת�����	
		}
		value/=50;
		ad=(float)value*0.0008056640625;
		ad=((1.43-ad)/0.0043)+25;
		return (int)(ad*1000);
}
