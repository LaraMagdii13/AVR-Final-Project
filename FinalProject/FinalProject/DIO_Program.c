/*
 * DIO_Program.c
 * Created: 24-Sep-23 10:08:55 PM
 * Author: Lara Magdi
 */ 

#include "DIO_Interface.h"

void DIO_SetPinMode(u8 PortID, u8 PinID, u8 PinMode){
	
	if((PortID<=3) && (PinID<=7) && ((PinMode==DIO_PIN_OUTPUT) || (PinMode==DIO_PIN_INPUT))){
	switch (PortID)
	{
		case DIO_PORTA:
		switch(PinMode)
		{
			case DIO_PIN_INPUT:
			ClrBit(DDRA,PinID);
			break;
			case DIO_PIN_OUTPUT:
			SetBit(DDRA,PinID);
			break;
		}
		break;
		
		
		case DIO_PORTB:
		switch(PinMode)
		{
			case DIO_PIN_INPUT:
			ClrBit(DDRB,PinID);
			break;
			case DIO_PIN_OUTPUT:
			SetBit(DDRB,PinID);
			break;
		}
		break;
		
		
		case DIO_PORTC:
		switch(PinMode)
		{
			case DIO_PIN_INPUT:
			ClrBit(DDRC,PinID);
			break;
			case DIO_PIN_OUTPUT:
			SetBit(DDRC,PinID);
			break;
		}
		break;
		
		
		case DIO_PORTD:
		switch(PinMode)
		{
			case DIO_PIN_INPUT:
			ClrBit(DDRD,PinID);
			break;
			case DIO_PIN_OUTPUT:
			SetBit(DDRD,PinID);
			break;
		}
		break;	
	}
  }
  else{
	  //Nothing
  }
}

void DIO_SetPinValue(u8 PortID, u8 PinID, u8 PinValue){
	
	if((PortID<=3) && (PinID<=7) && ((PinValue==DIO_PIN_HIGH) || (PinValue==DIO_PIN_LOW))){
	switch(PortID){
		
		case DIO_PORTA:
		switch(PinValue){
			case DIO_PIN_LOW:
			ClrBit(PORTA,PinID);
			break;
			case DIO_PIN_HIGH:
			SetBit(PORTA,PinID);
			break;
		}
		break;
		
		
		case DIO_PORTB:
		switch(PinValue){
			case DIO_PIN_LOW:
			ClrBit(PORTB,PinID);
			break;
			case DIO_PIN_HIGH:
			SetBit(PORTB,PinID);
			break;
		}
		break;
		
		
		case DIO_PORTC:
		switch(PinValue){
			case DIO_PIN_LOW:
			ClrBit(PORTC,PinID);
			break;
			case DIO_PIN_HIGH:
			SetBit(PORTC,PinID);
			break;
		}
		break;
		
		
		case DIO_PORTD:
		switch(PinValue){
			case DIO_PIN_LOW:
			ClrBit(PORTD,PinID);
			break;
			case DIO_PIN_HIGH:
			SetBit(PORTD,PinID);
			break;
		}
		break;
	}
  }
  else{
	  //Nothing
  }
}

void DIO_ReadPinValue(u8 PortID, u8 PinID, u8* PinValue){
	
	if((PortID<=3) && (PinID<=7) && (PinValue!=NULL)){
	switch(PortID){
		
		case DIO_PORTA:
		*PinValue=GetBit(PINA,PinID);
		break;
		
		case DIO_PORTB:
		*PinValue=GetBit(PINB,PinID);
		break;
		
		case DIO_PORTC:
		*PinValue=GetBit(PINC,PinID);
		break;
		
		case DIO_PORTD:
		*PinValue=GetBit(PIND,PinID);
		break;
	}
  }
  else{
	  //Nothing
  }
}

void DIO_TogglePinValue(u8 PortID, u8 PinID){
	
	if((PortID<=3) && (PinID<=7)){
		
		switch(PortID){
			case DIO_PORTA:
			TogBit(PORTA,PinID);
			break;
			
			case DIO_PORTB:
			TogBit(PORTB,PinID);
			break;
			
			case DIO_PORTC:
			TogBit(PORTC,PinID);
			break;
			
			case DIO_PORTD:
			TogBit(PORTD,PinID);
			break;
		}
	}
	else{
		//Do Nothing
	}
}

void DIO_ActivePinInPullUpResistance(u8 PortID, u8 PinID){
	
	if((PortID<=3) && (PinID<=7)){
	switch(PortID)
	{
		case DIO_PORTA:
		SetBit(PORTA,PinID);
		break;
		
		case DIO_PORTB:
		SetBit(PORTB,PinID);
		break;
		
		case DIO_PORTC:
		SetBit(PORTC,PinID);
		break;
		
		case DIO_PORTD:
		SetBit(PORTD,PinID);
		break;
	}
  }
  else{
	  //Nothing
  }
}

void DIO_SetPortMode(u8 PortID, u8 PortMode){
	switch (PortID)
	{
		case DIO_PORTA:
		switch(PortMode)
		{
			case DIO_PIN_INPUT:
			DDRA=0x00;
			break;
			case DIO_PIN_OUTPUT:
			DDRA=0xFF;
			break;
		}
		break;
		
		case DIO_PORTB:
		switch(PortMode)
		{
			case DIO_PIN_INPUT:
			DDRB=0x00;
			break;
			case DIO_PIN_OUTPUT:
			DDRB=0xFF;
			break;
		}
		break;
		
		case DIO_PORTC:
		switch(PortMode)
		{
			case DIO_PIN_INPUT:
			DDRC=0x00;
			break;
			case DIO_PIN_OUTPUT:
			DDRC=0xFF;
			break;
		}
		break;
		
		case DIO_PORTD:
		switch(PortMode)
		{
			case DIO_PIN_INPUT:
			DDRD=0x00;
			break;
			case DIO_PIN_OUTPUT:
			DDRD=0xFF;
			break;
		}
		break;
	}
}

void DIO_SetPortValue(u8 PortID, u8 PortValue){
	switch(PortID){
		case DIO_PORTA:
			PORTA=PortValue;
			break;
		
		case DIO_PORTB:
			PORTB=PortValue;
			break;
		
		case DIO_PORTC:
			PORTC=PortValue;
			break;
		
		case DIO_PORTD:
			PORTD=PortValue;
			break;
	}
}

void DIO_ReadPortValue(u8 PortID, u8* PortValue){
	switch(PortID){
		case DIO_PORTA:
		*PortValue=PINA;
		break;
		
		case DIO_PORTB:
		*PortValue=PINB;
		break;
		
		case DIO_PORTC:
		*PortValue=PINC;
		break;
		
		case DIO_PORTD:
		*PortValue=PIND;
		break;
	}
}

void DIO_TogglePortValue(u8 PortID){
		
		switch(PortID){
			case DIO_PORTA:
			PORTA=~PORTA;
			break;
			
			case DIO_PORTB:
			PORTB=~PORTB;
			break;
			
			case DIO_PORTC:
			PORTC=~PORTC;
			break;
			
			case DIO_PORTD:
			PORTD=~PORTD;
			break;
		}
}

void DIO_ActivePortInPullUpResistance(u8 PortID){
	switch(PortID)
	{
		case DIO_PORTA:
			PORTA = 0xff;
			break;
	
		case DIO_PORTB:
			PORTB = 0xff;
			break;
	
		case DIO_PORTC:
			PORTC = 0xff;
			break;
	
		case DIO_PORTD:
			PORTD = 0xff;
			break;
	}
}