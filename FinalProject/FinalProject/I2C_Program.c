/*
 * I2C_Program.c
 *
 * Created: 24-Nov-23 11:36:37 AM
 * Author: Dell
 */ 
 #include "BitMath.h"
 #include "STD.h"
 #include "I2C_Private.h"
 #include "I2C_Interface.h"

 void I2C_Init_Master(void){

	//Set Prescaller=1 >> Set Frequency=400KHz
	TWBR=12;
	ClrBit(TWSR,TWPS0);
	ClrBit(TWSR,TWPS1);

	//Set ACK
	SetBit(TWCR,TWEA);

	//Enable I2C Peripheral
	SetBit(TWCR,TWEN);
 }

 void I2C_Send_Start_Condition(void){
	//Request Start Condition
	SetBit(TWCR,TWSTA);

	//Clear Flag to Start Current Job
	SetBit(TWCR,TWINT);

	//Busy Wait for The Flag
	while(GetBit(TWCR,TWINT)==0);

	//Check ACK = SC ACK
	while(I2C_STATUS_VALUE != I2C_START_CONDITION_ACK);

 }

 void I2C_Send_Repeated_Start_Condition(void){
	//Request Start Condition
	SetBit(TWCR,TWSTA);

	//Clear Flag to Start Current Job
	SetBit(TWCR,TWINT);

	//Busy Wait for The Flag
	while(GetBit(TWCR,TWINT)==0);

	//Check ACK = RSC ACK
	while(I2C_STATUS_VALUE != I2C_REP_START_CONDITION_ACK);

 }

 void I2C_Send_Stop_Condition(void){
	//Request Stop Condition
	SetBit(TWCR,TWSTO);

	//Clear Flag to Start Current Job
	SetBit(TWCR,TWINT);
 }

 void I2C_Send_Slave_Add_With_Write(u8 SlaveAdd){
	
	if (SlaveAdd<128)
	{
		TWDR=(SlaveAdd<<1);

		//Select Write Operation
		ClrBit(TWDR,0);

		// Clear start condition bit
		ClrBit(TWCR,TWSTA);

		//Clear Flag to Start Current Job
		SetBit(TWCR,TWINT);

		//Busy Wait for The Flag
		while(GetBit(TWCR,TWINT)==0);

		//Check ACK = Master Transmit ( Slave Address + Write Request )
		while(I2C_STATUS_VALUE != I2C_SLAVE_ADDRESS_WRITE_ACK);
	}
 }

 void I2C_Send_Slave_Add_With_Read(u8 SlaveAdd){

	if (SlaveAdd<128)
	{
		TWDR=(SlaveAdd<<1);

		//Select Write Operation
		SetBit(TWDR,0);

		// Clear start condition bit
		ClrBit(TWCR,TWSTA);

		//Clear Flag to Start Current Job
		SetBit(TWCR,TWINT);

		//Busy Wait for The Flag
		while(GetBit(TWCR,TWINT)==0);

		//Check ACK = Master Transmit ( Slave Address + Read Request )
		while(I2C_STATUS_VALUE != I2C_SLAVE_ADDRESS_READ_ACK);
	}
 }

 void I2C_Send_Master_Data_Byte(u8 TxData){
	
	//Write Data Into Data Register
	TWDR=TxData;

	//Clear Flag to Start Current Job
	SetBit(TWCR,TWINT);

	//Busy Wait for The Flag
	while(GetBit(TWCR,TWINT)==0);

	//Check ACK = Master Transmit ( Slave Address + Read Request )
	while(I2C_STATUS_VALUE != I2C_MASTER_DATA_TRANSMIT_ACK);

 }

 void I2C_Receive_Master_Data_Byte_With_ACK(u8* RxData){
	if(RxData!=NULL)
	{
			//Clear Flag to Start Current Job
			SetBit(TWCR,TWINT);

			//Busy Wait for The Flag
			while(GetBit(TWCR,TWINT)==0);

			//Check ACK = Master Transmit ( Slave Address + Read Request )
			while(I2C_STATUS_VALUE != I2C_MASTER_DATA_RECIEVE_ACK);

			*RxData=TWDR;
	}
 }

 void I2C_Receive_Master_Data_Byte_With_No_ACK(u8* RxData){
	if (RxData!=NULL)
	{
		//Disable ACK
		ClrBit(TWCR,TWEA);	
			
		//Clear Flag to Start Current Job
		SetBit(TWCR,TWINT);

		//Busy Wait for The Flag
		while(GetBit(TWCR,TWINT)==0);

		//Check ACK = Master Transmit ( Slave Address + Read Request )
		while(I2C_STATUS_VALUE != I2C_MASTER_DATA_RECIEVE_No_ACK);

		*RxData=TWDR;	

		//Enable ACK
		SetBit(TWCR,TWEA);	
	}
 }