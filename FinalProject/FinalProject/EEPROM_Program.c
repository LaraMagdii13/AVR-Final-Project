/*
 * EEPROM_Program.c
 *
 * Created: 25-Nov-23 11:31:25 AM
 * Author: Dell
 */ 

 #define F_CPU 1000000UL
 #include <util/delay.h>
 #include "STD.h"
 #include "BitMath.h"
 #include "I2C_Interface.h"
 #include "EEPROM_Interface.h"
 #include "EEPROM_Private.h"

 void EEPROM_Init(void){
	I2C_Init_Master();
 }

 void EEPROM_Write_Byte(u16 Address,u8 Data){

		u8 DeviceAddress=(Address>>8)|EEPROM_FIXED_ADDRESS;

		//Send Start Condition
		I2C_Send_Start_Condition();

		//Send lave Address With Write
		I2C_Send_Slave_Add_With_Write(DeviceAddress);

		//Send Word Address
		I2C_Send_Master_Data_Byte((u8)Address);

		//Send Byte Data
		I2C_Send_Master_Data_Byte(Data);

		//Send Stop Condition
		I2C_Send_Stop_Condition();

		// Self-Timed Write Cycle Delay
		_delay_ms(5);
 }

 void EEPROM_Read_Byte(u16 Address, u8* Data){
		if(Data!=NULL){
			
			u8 DeviceAddress=(Address>>8)|EEPROM_FIXED_ADDRESS;

			//Send Start Condition
			I2C_Send_Start_Condition();

			//Send lave Address With Write
			I2C_Send_Slave_Add_With_Write(DeviceAddress);

			//Send Word Address
			I2C_Send_Master_Data_Byte((u8)Address);

			//Send Repeated Start Condition
			I2C_Send_Repeated_Start_Condition();

			//Send Slave Address With Read
			I2C_Send_Slave_Add_With_Read(DeviceAddress);

			//Receive Byte Data NACK
			I2C_Receive_Master_Data_Byte_With_No_ACK(Data);

			//Send Stop Condition
			I2C_Send_Stop_Condition();
			
			// Self-Timed Write Cycle Delay
			_delay_ms(5);
		}
 }

 void EEPROM_Write_Page(u16 Address, u8*Data, u8 DataSize){
	if((Data!=NULL) && (DataSize<=16)){
		
		u8 DeviceAddress=(Address>>8)|EEPROM_FIXED_ADDRESS;

		//Send Start Condition
		I2C_Send_Start_Condition();

		//Send lave Address With Write
		I2C_Send_Slave_Add_With_Write(DeviceAddress);

		//Send Word Address
		I2C_Send_Master_Data_Byte((u8)Address);

		u8 Counter; 
		for (Counter=0;Counter<=DataSize;Counter++)
		{
			//Send Byte Data
			I2C_Send_Master_Data_Byte(Data[Counter]);
		}
		
		//Send Stop Condition
		I2C_Send_Stop_Condition();

		// Self-Timed Write Cycle Delay
		_delay_ms(5);	
	}
 }

 void EEPROM_Read_Page(u16 Address, u8*Data, u8 DataSize){
	if((Data!=NULL) && (DataSize<=16)){
		
		u8 DeviceAddress=(Address>>8)|EEPROM_FIXED_ADDRESS;

		//Send Start Condition
		I2C_Send_Start_Condition();

		//Send lave Address With Write
		I2C_Send_Slave_Add_With_Write(DeviceAddress);

		//Send Word Address
		I2C_Send_Master_Data_Byte((u8)Address);

		//Send Repeated Start Condition
		I2C_Send_Repeated_Start_Condition();

		//Send Slave Address With Read
		I2C_Send_Slave_Add_With_Read(DeviceAddress);

		u8 Counter;
		for (Counter=0;Counter<DataSize-1;Counter++)
		{
			//Receive Byte Data 
			I2C_Receive_Master_Data_Byte_With_ACK(&Data[Counter]);
		}

		//Receive Last Byte Data
		I2C_Receive_Master_Data_Byte_With_No_ACK(&Data[Counter]);
		
		//Send Stop Condition
		I2C_Send_Stop_Condition();

		// Self-Timed Write Cycle Delay
		_delay_ms(5);
	}
 }