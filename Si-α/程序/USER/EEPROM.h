#ifndef __EEPROM_H__
#define __EEPROM_H__
//STC12C5A60S2��EEPROM��1KB����������
//��һ��������ʼ��ַ:0x0000~0x01ff<0~511>(��512�ֽ�)
//�ڶ���������ʼ��ַ:0x0200~0x03ff<512~1023>(��512�ֽ�)
unsigned char EepromReadByte(unsigned char addr);
void EepromWriteByte(unsigned char addr, unsigned char dat);
#endif
