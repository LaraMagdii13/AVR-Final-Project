/*
 * Timer0_Program.c
 *
 * Created: 27-Oct-23 5:34:53 PM
 *  Author: Lara
 */ 

 #include "BitMath.h"
 #include "STD.h"
 #include "Timer0_Config.h"
 #include "Timer0_Private.h"
 #include "Timer0_Interface.h"

 volatile static u16 Private_CTC_Counter;
 static void(*Private_P_CallBackOVF)(void)=NULL;
 static void(*Private_P_CallBackCTC)(void)=NULL;

 void TimerInit(void){
	
#if TimerMode == TimerNormalMode
	// Set Normal Mode
	ClrBit(TCCR0,WGM00);
	ClrBit(TCCR0,WGM01);

	// Init Timer With Reload Value
	TCNT0 = TIMER0_RELOAD_VALUE;

	// Enable OVF Interrupt
	SetBit(TIMSK,TOIE0); 

#elif TimerMode == TimerCTCMode
	// Set CTC Mode
	ClrBit(TCCR0,WGM00);
	SetBit(TCCR0,WGM01);

	// Enable OC Interrupt
	SetBit(TIMSK,OCIE0);

#elif TimerMode == TimerFastPWMMode
	// Set Fast PWM Mode
	SetBit(TCCR0,WGM00);
	SetBit(TCCR0,WGM01);

	// Set Non-Inverting 
	ClrBit(TCCR0,COM00);
	SetBit(TCCR0,COM01);

#endif

 }

 void TimerSetCompareMatchValue(u8 CompareValue){

	OCR0=CompareValue;
 }

 void TimerSetDutyCycle(u8 Duty){

	if(Duty<=100){
		OCR0=((u16)(Duty*256)/100)-1;
	}
	
 }

 void TimerSetDelay_ms_UsingCTC(u16 Delay_ms){
	//under condition of tick time 4 MicroSec & OCR 249
	OCR0=249;
	Private_CTC_Counter=Delay_ms;

 }

 void TimerStart(void){
   // Select Prescaler Value = 64
   SetBit(TCCR0,CS00);
   SetBit(TCCR0,CS01);
   ClrBit(TCCR0,CS02);

 }

 void TimerStop(void){
	// Select Prescaler Value = 0
	ClrBit(TCCR0,CS00);
	ClrBit(TCCR0,CS01);
	ClrBit(TCCR0,CS02);

 }

 void TimerSetCallBackOVF(void(*PtrToFunc)(void)){

		if (PtrToFunc!=NULL)
		{
			Private_P_CallBackOVF=PtrToFunc;
		}
 }

 void TimerSetCallBackCTC(void(*PtrToFunc)(void)){
 		if (PtrToFunc!=NULL)
 		{
		 	Private_P_CallBackCTC=PtrToFunc;
 		}
 }

 void __vector_11 (void) __attribute__ ((signal));
 void __vector_11 (void) {

	 static u16 OVFcounter=0;
	 OVFcounter++;

	 if (Timer0_OVERFLOW_COUNTER == OVFcounter)
	 {
		 TCNT0=TIMER0_RELOAD_VALUE;

		 OVFcounter=0;
		 
		 if (Private_P_CallBackOVF!=NULL)
		 {
				Private_P_CallBackOVF();
		 }
		 
	 }
 }

  void __vector_10 (void) __attribute__ ((signal));
  void __vector_10 (void){

		static u16 CTCcounter=0;
		CTCcounter++;

		if (Timer0_CTC_COUNTER == CTCcounter)
		{
			CTCcounter=0;
			
			if (Private_P_CallBackCTC!=NULL)
			{
				Private_P_CallBackCTC();
			}
			
		}
  }