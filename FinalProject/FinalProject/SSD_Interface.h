/*
 * SSD_Interface.h
 *
 * Created: 27-Nov-23 10:06:16 PM
 *  Author: Dell
 */ 


#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define SSD_ONE  1
#define SSD_TWO  2

void SSD_Init();
void SSD_Write_Number(u8 SSD_ID, u8 Number);
void SSD_Write_Multiple_Number(u8 Number);
static void PRV_WriteHalfPort(u8 value);
void SSD_Disable();



#endif /* SSD_INTERFACE_H_ */