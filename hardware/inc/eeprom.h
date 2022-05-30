#ifndef __EEPROM_H_
#define __EEPROM_H_
void EEEPROM_Password_Init(void);
void EEPROM_Write_Byte(unsigned char addr,unsigned char data);
unsigned char EEPROM_Read_Byte(unsigned char add);






#endif 
