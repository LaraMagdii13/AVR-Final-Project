/*
 * ADC_Program.c
 *
 * Created: 15-Oct-23 9:07:45 PM
 *  Author: Lara Magdi
 */ 
 #include "BitMath.h"
 #include "STD.h"
 #include "ADC_Interface.h"
 #include "ADC_Private.h"

 void ADC_init(u8 ReferenceVoltage){

	switch(ReferenceVoltage){

		case ADC_REFERENCE_AVCC:
		SetBit(ADMUX,REFS0);
		ClrBit(ADMUX,REFS1);
		break;

		case ADC_REFERENCE_AVREF:
		ClrBit(ADMUX,REFS0);
		ClrBit(ADMUX,REFS1);
		break;

		case ADC_REFERENCE_INTERNAL:
		SetBit(ADMUX,REFS0);
		SetBit(ADMUX,REFS1);
		break;
	}

	ClrBit(ADMUX,ADLAR); //Right Adjustment

	ClrBit(ADCSRA,ADATE); //Closing auto trigger (working on single conversion mode)

	ClrBit(ADCSRA,ADIE); //Disable ADC interrupt(working with blocking method)

	//Pre-scaler 128 for 16MHz
	SetBit(ADCSRA,ADPS0);
	SetBit(ADCSRA,ADPS1);
	SetBit(ADCSRA,ADPS2); 

	SetBit(ADCSRA,ADEN); //ADC Enable (dayman hankhaly el enable akher khatwa)
 }

 void ADC_GetDigitalValue(u8 ChannelNum, u16* DigitalValue){

	//Select channel
	if((ChannelNum<32) && (DigitalValue!=NULL)){

		ADMUX &= 0xE0; //clear ADMUX channel bits
		ADMUX |= ChannelNum; //selecting channel number

		//Start conversion
		SetBit(ADCSRA,ADSC);
		
		//Busy wait for the flag
		while (GetBit(ADCSRA,ADIF) == 0);

		//Clearing flag (write one to clear)
		SetBit(ADCSRA,ADIF);

		//Read digital flag from ADC data register
		*DigitalValue= ADC_u16;
	}
 }