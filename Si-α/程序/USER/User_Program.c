#include "User_Program.h"
void User_Program()
{
	LCD1602_Writecom(0x80);
	LCD1602_SendString("User Programe");
	LCD1602_Writecom(0x80+0x40);
	LCD1602_SendString("Hello 8051");
	  //�˴�д���û�����
}
/*
unsigned int Get_AD_Result(unsigned char chunnel);

*/