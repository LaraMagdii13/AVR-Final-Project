/*
 * Global_Interrupt_Program.c
 *
 * Created: 13-Oct-23 5:22:40 PM
 *  Author: Dell
 */ 

#include "BitMath.h"
#include "Global_Interrupt_Interface.h"
#include "Global_Interrupt_Private.h"

void Enable_Global_Interrupt(void){

	SetBit(SREG,I);

}
void Disable_Global_Interrupt(void){

	ClrBit(SREG,I);

}