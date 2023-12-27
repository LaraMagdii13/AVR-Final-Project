/*
 * I2C_Private.h
 *
 * Created: 24-Nov-23 11:35:55 AM
 * Author: Dell
 */ 


#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

/*Two Wire Interface (I2C)*/

#define I2C_STATUS_VALUE			     (TWSR&0xF8)
#define I2C_START_CONDITION_ACK			 0x08
#define I2C_REP_START_CONDITION_ACK		 0x10
#define I2C_SLAVE_ADDRESS_WRITE_ACK		 0x18
#define I2C_SLAVE_ADDRESS_READ_ACK		 0x40
#define I2C_MASTER_DATA_TRANSMIT_ACK	 0x28
#define I2C_MASTER_DATA_RECIEVE_ACK		 0x50
#define I2C_MASTER_DATA_RECIEVE_No_ACK   0x58


/* TWI REGISTERS */

// TWI Bit Rate Register
#define TWBR         (*(volatile u8*)0x20)

// TWI Control Register
#define TWCR         (*(volatile u8*)0x56)
#define TWIE         0
#define TWEN         2
#define TWWC         3
#define TWSTO        4
#define TWSTA        5
#define TWEA         6
#define TWINT        7


// TWI Status Register
#define TWSR         (*(volatile u8*)0x21)
#define TWPS0        0
#define TWPS1        1

// TWI Data Register
#define TWDR         (*(volatile u8*)0x23)

// TWI (Slave) Address Register
#define TWAR         (*(volatile u8*)0x22)
#define TWGCE        0


#endif /* I2C_PRIVATE_H_ */