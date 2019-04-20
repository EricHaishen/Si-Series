#ifndef _CAMERA_H_
#define _CAMERA_H_
#define Camera_Init_Fail 1
#define Camera_Init_Success 0
uint8_t Camera_Init(unsigned char Light_Mode,unsigned char Effect);
		/**
		* Light_Mode,������Χ[0~5]��       Effect��������Χ[0~6]:
				@arg 0���Զ�												@arg 0:����
				@arg 1������												@arg 1:�ڰ�
				@arg 2������												@arg 2:ƫ��
				@arg 3���칫��											@arg 3:����
				@arg 4������												@arg 4:ƫ��
				@arg 5��ҹ��												@arg 5:ƫ��
																						@arg 6:����
    */
void FIFO_PREPARE(void);
uint16_t READ_FIFO_PIXEL(void);
void OV7725_Window_Set(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height,uint8_t QVGA_VGA);
#endif
