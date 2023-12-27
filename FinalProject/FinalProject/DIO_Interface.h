/*
 * DIO_Interface.h
 * Created: 24-Sep-23 10:09:16 PM
 * Author: Lara Magdi
 */ 

#include "STD.h"
#include "BitMath.h"
#include "DIO_Private.h"

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN_INPUT 0
#define DIO_PIN_OUTPUT 1

#define DIO_PIN0 0 
#define DIO_PIN1 1 
#define DIO_PIN2 2 
#define DIO_PIN3 3 
#define DIO_PIN4 4 
#define DIO_PIN5 5 
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_PIN_LOW 0
#define DIO_PIN_HIGH 1

#define FAIL 0
#define PASS 1


void DIO_SetPinMode(u8 PortID, u8 PinID, u8 PinMode);
void DIO_SetPinValue(u8 PortID, u8 PinID, u8 PinValue);
void DIO_ReadPinValue(u8 PortID, u8 PinID, u8* PinValue);
void DIO_TogglePinValue(u8 PortID, u8 PinID);
void DIO_ActivePinInPullUpResistance(u8 PortID, u8 PinID);

void DIO_SetPortMode(u8 PortID, u8 PinMode);
void DIO_SetPortValue(u8 PortID, u8 PinValue);
void DIO_ReadPortValue(u8 PortID, u8* PinValue);
void DIO_TogglePortValue(u8 PortID);
void DIO_ActivePortInPullUpResistance(u8 PortID);

#endif /* DIO_INTERFACE_H_ */