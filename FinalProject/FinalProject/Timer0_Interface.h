/*
 * Timer0_Interface.h
 *
 * Created: 27-Oct-23 5:35:30 PM
 *  Author: Dell
 */ 

  #include "BitMath.h"
  #include "STD.h"
  #include "Timer0_Config.h"
  #include "Timer0_Private.h"

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

void TimerInit(void);
void TimerStart(void);
void TimerStop(void);
void TimerSetCallBackOVF(void(*PtrToFunc)(void));
void TimerSetCallBackCTC(void(*PtrToFunc)(void));
void TimerSetCompareMatchValue(u8 CompareValue);
void TimerSetDelay_ms_UsingCTC(u16 Delay_ms);
void TimerSetDutyCycle(u8 Duty);


#endif /* TIMER0_INTERFACE_H_ */