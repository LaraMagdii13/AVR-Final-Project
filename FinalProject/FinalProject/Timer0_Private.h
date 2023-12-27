/*
 * Timer0_Private.h
 *
 * Created: 27-Oct-23 5:35:09 PM
 *  Author: Dell
 */ 
  #include "BitMath.h"
  #include "STD.h"

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

#define TimerNormalMode           1
#define TimerCTCMode              2
#define TimerFastPWMMode          3

// Timer/Counter Control Register
#define TCCR0            (*(volatile u8*)0x53)
#define CS00             0
#define CS01             1
#define CS02             2
#define WGM01            3
#define COM00            4
#define COM01            5
#define WGM00            6
#define FOC0             7

// Timer/Counter Register
#define TCNT0            (*(volatile u8*)0x52)

// Output Compare Register
#define OCR0             (*(volatile u8*)0x5C)

// Timer/Counter Interrupt Mask Register
#define TIMSK            (*(volatile u8*)0x59)
#define TOIE0            0
#define OCIE0            1

// Timer/Counter Interrupt Flag Register
#define TIFR             (*(volatile u8*)0x58)
#define TOV0             0
#define OCF0             1



#endif /* TIMER0_PRIVATE_H_ */