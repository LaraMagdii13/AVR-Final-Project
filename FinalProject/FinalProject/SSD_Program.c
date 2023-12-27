/*
 * SSD_Program.c
 *
 * Created: 27-Nov-23 10:05:52 PM
 *  Author: Dell
 */ 
 #define F_CPU 16000000UL
 #include <util/delay.h>
 #include "STD.h"
 #include "BitMath.h"
 #include "DIO_Interface.h"
 #include "SSD_Interface.h"

 u8 Sev_Seg[10]={
	 0x40, // 0
	 0x79, // 1
	 0x24, // 2
	 0x30, // 3
	 0x19, // 4
	 0x12, // 5
	 0x02, // 6
	 0x78, // 7
	 0x00, // 8
	 0x10  // 9
	 };
 void SSD_Init(){

 DIO_SetPortMode(DIO_PORTB,DIO_PIN_OUTPUT);
 DIO_SetPortMode(DIO_PORTD,DIO_PIN_OUTPUT);

 }




 void SSD_Write_Number(u8 SSD_ID, u8 Number){

	if(Number<=9){

		switch (SSD_ID)
		{
			case SSD_ONE:
				DIO_SetPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_HIGH);
				PRV_WriteHalfPort(Number);
				break;

			case SSD_TWO:
				DIO_SetPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_HIGH);
				PRV_WriteHalfPort(Number);
				break;
		}
	}

 }

 void SSD_Write_Multiple_Number(u8 Number){
	DIO_SetPortValue(DIO_PORTD,Sev_Seg[Number%10]);
	DIO_SetPortValue(DIO_PORTB,Sev_Seg[Number/10]);
	/*if (Number<=99)
	{
		DIO_SetPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_LOW);
		DIO_SetPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_LOW);
		PRV_WriteHalfPort(Number/10);
		DIO_SetPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_HIGH);
		_delay_ms(10);
		DIO_SetPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_LOW);
		PRV_WriteHalfPort(Number%10);
		DIO_SetPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_HIGH);
		_delay_ms(10);
		DIO_SetPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_LOW);

	}*/
 }

  static void PRV_WriteHalfPort(u8 value){

	  DIO_SetPinValue(DIO_PORTA,DIO_PIN4,GetBit(value,0));
	  DIO_SetPinValue(DIO_PORTA,DIO_PIN5,GetBit(value,1));
	  DIO_SetPinValue(DIO_PORTA,DIO_PIN6,GetBit(value,2));
	  DIO_SetPinValue(DIO_PORTA,DIO_PIN7,GetBit(value,3));
  }

  void SSD_Disable()
  {
		DIO_SetPortValue(DIO_PORTD,0xff);
		DIO_SetPortValue(DIO_PORTB,0xff);
  }