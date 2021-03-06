#include "Port.h"
#include "DS18B20.h"
unsigned int wendu = 0x00;
void Temp_Delay(unsigned char a1,b1,c1)
{
		unsigned char a,b,c;
		for(a=0;a<a1;a++)
			for(b=0;b<b1;b++)
				for(c=0;c<c1;c++);
}
/*****************DS18B20******************/ 
void Init_Ds18b20(void)     //DS18B20???send reset and initialization command
{
		DS18B20 = 1;                     //DQ??,??????
		Temp_Delay(1,1,1);                  //????  10us
		DS18B20 = 0;                    //???????
		Temp_Delay(6,1,63); //600  us      //????,????480us
		//Delay(1,1,15); //20us
		DS18B20 = 1;                    //????,??????
		Temp_Delay(5,1,63); //500us               //???????,????DS18B20???????
}
unsigned char Read_One_Byte()       //?????????read a byte date                          //????,?????????????????
{
		unsigned char i   = 0;
		unsigned char dat = 0;
		for(i=8;i>0;i--)
		{
			DS18B20 = 0;                  //?????,??1us??????                   //???????????15us?????????
			_nop_();                 //?????1us,???????
			dat >>= 1;               //???????????,???????????
			DS18B20 = 1;                  //????,??DS18B20?????,?????????
			Temp_Delay(1,1,1);        //??10us,???????????,?????????????????15us??????
			if(DS18B20)                   //???????
			{
				dat |= 0x80;            //????1,?DQ?1,???dat?????1;??0,??????,???0
			}        
			Temp_Delay(1,1,8);       //20us        //??????,????????60us?
		}
	return (dat);
}
void Write_One_Byte(unsigned char dat)
{
		unsigned char i = 0;
		for(i=8;i>0;i--)
		{
			DS18B20 = 0;                        //????
			_nop_();                       //?????1us,?????(???0????1??)??
			DS18B20 = dat&0x01;                 //???????????                             //??15us?DS18B20???????
			Temp_Delay(1,1,15);               //??????????60us
			DS18B20 = 1;                        //???,??????,
			dat >>= 1;
			Temp_Delay(1,1,1);
		}
}
unsigned int Get_Temp()                   //????get the wenduerature
{
	while(1)
	{
		float tt;
		unsigned char a,b;
		Init_Ds18b20();                //???
		Write_One_Byte(0xcc);          //??ROM??
		Write_One_Byte(0x44);          //??????
		Init_Ds18b20();                 //???
		Write_One_Byte(0xcc);          //??ROM??
		Write_One_Byte(0xbe);          //??????
		a = Read_One_Byte();           //????????????LSB
		b = Read_One_Byte();           //????????????MSB
		wendu = b;                      //???????????wendu
		wendu <<= 8;                    //???8????wendu????????
		wendu = wendu|a;                //???????????
		tt = wendu*0.0625;              //??????????                            //??????????????0.0625?
		wendu = tt*10+0.5;               //????                             //?????????????
		if(wendu<500&&wendu>0)
			break;
	}
	return wendu;
}