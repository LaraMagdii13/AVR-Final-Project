/*
 * ADC_Interface.h
 *
 * Created: 15-Oct-23 9:08:00 PM
 *  Author: Lara Magdi
 */ 
 #include "STD.h"

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define  ADC_CHANNEL0   0
#define	 ADC_CHANNEL1   1
#define	 ADC_CHANNEL2   2
#define	 ADC_CHANNEL3   3
#define	 ADC_CHANNEL4   4
#define	 ADC_CHANNEL5   5
#define	 ADC_CHANNEL6   6
#define	 ADC_CHANNEL7   7

#define ADC_REFERENCE_AVCC     1
#define ADC_REFERENCE_AVREF    2
#define ADC_REFERENCE_INTERNAL 3

void ADC_init(u8 ReferenceVoltage);
void ADC_GetDigitalValue(u8 ChannelNum, u16* DigitalValue);

#endif /* ADC_INTERFACE_H_ */