/*
 * FinalProject.c
 *
 * Created: 14-Dec-23 8:00:35 PM
 * Author : Dell
 */ 

#include "BitMath.h"
#include "STD.h"
#include <util/delay.h>
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "SSD_Interface.h"
#include "Timer0_Interface.h"
#include "Global_Interrupt_Interface.h"
#include "EEPROM_Interface.h"
#define F_CPU 4000000UL

volatile u16 GlobCurrentTemp=0;
volatile u8 GlobAvgTemp=60; 
volatile u8 GlobCounter=0;
volatile u8 TempData[10]={0};
volatile u8 ModeFlag=0;
volatile u8 desTemp=60;

u32 App_Get_Temp()
{
	u16 digital;
	ADC_GetDigitalValue(ADC_CHANNEL1,&digital);
	u32 analogVal=(((u32)digital*5000UL)/1024);
	analogVal/=10;
	return analogVal;
}//Converting analog value (value from temp sensor) to digital value 

void  ReadTemp()
{
	if (ModeFlag==0)
	{
		if(GlobCounter<10)
		{
			TempData[GlobCounter]=App_Get_Temp();
			SSD_Write_Multiple_Number(TempData[GlobCounter]);

			GlobCurrentTemp+=TempData[GlobCounter];
			GlobCounter++;
		}
		else
		{
			GlobCounter=0;
			memset(TempData,0,10);
			GlobAvgTemp=GlobCurrentTemp/10;
			GlobCurrentTemp=0;
		}
	}
}//getting the average temp value after every 10 readings

void App_Init_Modules(void)
{
	u8 E2data[2]={0}; //EEPROM init
	SSD_Init(); //7 seg init
	DIO_SetPinMode(DIO_PORTA,DIO_PIN0,DIO_PIN_OUTPUT);	//fan control	
	DIO_SetPinMode(DIO_PORTA,DIO_PIN1,DIO_PIN_INPUT);	//sensor control
	DIO_SetPinMode(DIO_PORTC,DIO_PIN5,DIO_PIN_OUTPUT);	//heater control
	DIO_SetPinMode(DIO_PORTC,DIO_PIN4,DIO_PIN_INPUT);	//-5
	DIO_SetPinMode(DIO_PORTC,DIO_PIN2,DIO_PIN_INPUT);	//+5
	DIO_SetPinMode(DIO_PORTC,DIO_PIN3,DIO_PIN_INPUT);	//ON OFF
	DIO_SetPinMode(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT);	//LED
	ADC_init(ADC_REFERENCE_AVCC); 
	
	//Timer control 
	Enable_Global_Interrupt();
	TimerInit();
	TimerSetCompareMatchValue(249);
	TimerSetCallBackCTC(ReadTemp);
	TimerStart();

	//EEPROM control
	EEPROM_Init();
	E2data[0]=desTemp/10; //First digit
	E2data[1]=desTemp%10; //Second digit
	EEPROM_Write_Page(0,E2data,2);

}//initializing all components

void APP_TurnOnHeater()
{
	DIO_SetPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_HIGH);
	DIO_TogglePinValue(DIO_PORTC,DIO_PIN7);
	_delay_ms(1000);
}//Turning on heater

void APP_TurnOffHeater()
{
	DIO_SetPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_LOW);
}//Turning off heater

void APP_TurnOnCooler()
{
	DIO_SetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_HIGH);
	DIO_SetPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_HIGH);
}//Turning on cooler (Fan)

void APP_TurnOffCooler()
{
	DIO_SetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_LOW);
}//Turning off cooler (Fan)

void App_TempControlMode()
{
	if (GlobCounter==0 )
	{
		if (GlobAvgTemp<desTemp)
		{
			APP_TurnOnHeater();
			APP_TurnOffCooler();
		}//when temp is less than 60
		else if (GlobAvgTemp>desTemp)
		{
			APP_TurnOnCooler();
			APP_TurnOffHeater();
		}//when temp is greater than 60
		else if (GlobAvgTemp==desTemp)
		{
			DIO_SetPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
			APP_TurnOffHeater();
			APP_TurnOffCooler();
		}//when temp is equal 60
	}
}//Controlling app depending on desired temp

void APP_TurnedOff()
{
	APP_TurnOffCooler();
	APP_TurnOffHeater();
	DIO_SetPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_LOW);
	SSD_Disable();
}//Turning off the system

int main(void)
{
	
	u8 B1,B2,B3; //3 buttons of the systems
	u8 ON_OFF_State=0;
	u8 DesTempSet=0;
	u8 E2data[2]={0};

	App_Init_Modules();


	while (1)
	{
		if(ON_OFF_State==0)
		{
			App_TempControlMode();//control heater and cooler

			DIO_ReadPinValue(DIO_PORTC,DIO_PIN4,&B1);//-5 button
			DIO_ReadPinValue(DIO_PORTC,DIO_PIN2,&B2);//+5 button

			if ((B2==DIO_PIN_HIGH) || (B1==DIO_PIN_HIGH) || ModeFlag==1)
			{
				if (ModeFlag == 1)
				{
					if ((B1==DIO_PIN_HIGH) && (desTemp>35))
					{
						desTemp-=5;
						DesTempSet=0;
					}//When -5 button is pressed
					else if ((B2==DIO_PIN_HIGH) && (desTemp<75))
					{
						desTemp+=5;
						DesTempSet=0;
					}//When +5 button is pressed
				}//End of modeflag==0

				ModeFlag=1;
				SSD_Write_Multiple_Number(desTemp);
				_delay_ms(1000);
				SSD_Disable();
				_delay_ms(1000);
				DesTempSet++;
				//Blinking for 5 seconds (set temp mode)

				if(DesTempSet==5)
				{
					ModeFlag=0;
					DesTempSet=0;
				}//Stop set temp mode
					
			}//end temp setting
		 }//end of one mode

		DIO_ReadPinValue(DIO_PORTC,DIO_PIN3,&B3); //on off button
		if(B3==DIO_PIN_HIGH)
		{	
			if (ON_OFF_State==1) //system were off then read from EEPROM
			{
				memset(E2data,0,2);
				EEPROM_Read_Page(0,E2data,2);
				desTemp=((E2data[0])*10)+(E2data[1]);
			}
			TogBit(ON_OFF_State,0);	//toggle system state
		}//Turn on system and show saved temp from EEPROM

		while(B3==DIO_PIN_HIGH) DIO_ReadPinValue(DIO_PORTC,DIO_PIN3,&B3);//Read button 3 finite loop

		if(GetBit(ON_OFF_State,0)==1)
		{
			APP_TurnedOff();
			E2data[0]=desTemp/10;
			E2data[1]=desTemp%10;
			EEPROM_Write_Page(0,E2data,2);
		}//Turn off system and save temp in EEPROM
	}
}

