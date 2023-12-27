/*
 * EEPROM_Interface.h
 *
 * Created: 25-Nov-23 11:31:56 AM
 * Author: Dell
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_Init(void);
void EEPROM_Write_Byte(u16 Address,u8 Data);
void EEPROM_Read_Byte(u16 Address, u8* Data);
void EEPROM_Write_Page(u16 Address, u8*Data, u8 DataSize);
void EEPROM_Read_Page(u16 Address, u8*Data, u8 DataSize);


#endif /* EEPROM_INTERFACE_H_ */