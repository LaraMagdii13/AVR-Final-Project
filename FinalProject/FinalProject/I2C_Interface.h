/*
 * I2C_Interface.h
 *
 * Created: 24-Nov-23 11:36:13 AM
 * Author: Dell
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

void I2C_Init_Master(void);
void I2C_Send_Start_Condition(void);
void I2C_Send_Repeated_Start_Condition(void);
void I2C_Send_Stop_Condition(void);
void I2C_Send_Slave_Add_With_Write(u8 SlaveAdd);
void I2C_Send_Slave_Add_With_Read(u8 SlaveAdd);
void I2C_Send_Master_Data_Byte(u8 TxData);
void I2C_Receive_Master_Data_Byte_With_ACK(u8* RxData);
void I2C_Receive_Master_Data_Byte_With_No_ACK(u8* RxData);

#endif /* I2C_INTERFACE_H_ */