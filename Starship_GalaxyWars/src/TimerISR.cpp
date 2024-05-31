#include "TimerISR.h"
#include "SerialMonitor.h"
#include <util/atomic.h>

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long __avr__TimerTop = 1;   // Start count from here, down to 0. Default 1ms
unsigned long __avr__TimerCount = 0; // Current internal count of 1ms ticks

uint32_t volatile timerMS = 0;

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long timerPeriod) 
{
	__avr__TimerTop = timerPeriod;
	__avr__TimerCount = __avr__TimerTop;
}

void TimerOn() 
{
	SREG   = 0b10000000; // Enable Global Interrupts

	// Task Timer
	TCCR0A = 0b00000011; // Fast PWM Mode.
	TCCR0B = 0b00001011; // prescalar 64 (4 microsecond tick), or 4 microseconds per timer count increment
	OCR0A  = 250;        // 1000 microseconds (1ms) / 4 microsecond tick = 250 exactly. 
						 // 	This will let us have an (overflow) interrupt every 1 milisecond.
	TCNT0  = 0;          // Initialize counter to 0.
	TIMSK0 = 0b00000010; // Enable Compare match interrupt (A), No Overflow

	// Timer2 
	TCCR2A = 0b00000010; // CTC
	TCCR2B = 0b00000011; // prescalar 64 (4 microsecond tick), or 4 microseconds per timer count increment
	OCR2A  = 250;        // 1000 microseconds (1ms) / 4 microsecond tick = 250 exactly. 
						 // 	This will let us have an (overflow) interrupt every 1 milisecond.
	TCNT2  = 0;          // Initialize counter to 0.
	TIMSK2 = 0b00000010; // Enable Compare match interrupt (A), No Overflow
}

void TimerOff() 
{
	TCCR0B 	= 0x00; // bit3bit2bit1bit0=0000: timer off
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER0_COMPA_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	__avr__TimerCount--; 			// Count down to 0 rather than up to TOP
	if (__avr__TimerCount == 0) { 	// results in a more efficient compare
		TimerISR(); 				// Call the ISR that the user uses
		__avr__TimerCount = __avr__TimerTop;
	}
}

ISR(TIMER2_COMPA_vect)
{
	timerMS++;
}

uint32_t GetTimeMS()
{
	uint32_t ret;

	ATOMIC_BLOCK(ATOMIC_FORCEON) 
	{
		ret = timerMS;
	}
	return ret;
}
