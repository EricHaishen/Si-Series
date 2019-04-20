#include "System.h"
#include "SPI1.h"
void SPI1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); //PA5.6.7����
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//ѡ��ȫ˫��SPIģʽ
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;     //����ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8λSPI
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;       //ʱ�����ոߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;      //�ڵڶ���ʱ�Ӳɼ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		  //Nssʹ���������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//�����λ��ʼ����
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Cmd(SPI1, ENABLE);
	SPI_Init(SPI1, &SPI_InitStructure);
}   
void SPI1_SetSpeed(uint8_t speed)
{
	SPI1->CR1 &= 0xFFC7; 
	SPI1->CR1 |= speed;
	SPI_Cmd(SPI1, ENABLE);
}
uint8_t SPI1_WriteReadData(uint8_t dat)
{
	uint16_t i = 0;
 	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
	{
		i++;
		if(i > 10000)
		{
			return 0xFF;
		}
	}
   SPI_I2S_SendData(SPI1, dat);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
	{
		
	}
 	return SPI_I2S_ReceiveData(SPI1);		
}
