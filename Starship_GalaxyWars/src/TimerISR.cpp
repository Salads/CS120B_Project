#include "TimerISR.h"
#include "SerialMonitor.h"

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long __avr__TimerTop = 1;   // Start count from here, down to 0. Default 1ms
unsigned long __avr__TimerCount = 0; // Current internal count of 1ms ticks

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long timerPeriod) 
{
	__avr__TimerTop = timerPeriod;
	__avr__TimerCount = __avr__TimerTop;
}

void TimerOn() 
{
	// Task Timer
	TCCR0A = 0b00000011; // Fast PWM Mode.
	TCCR0B = 0b00001011; // prescalar 64 (4 microsecond tick)
	OCR0A  = 250;        // 1000 microseconds (1ms) / 4 microsecond tick = 250 exactly. 
						 // 	This will let us have an interrupt every 1 milisecond.
	TCNT0  = 0;          // Initialize counter to 0.
	SREG   = 0b10000000; // Enable Global Interrupts
	TIMSK0 = 0b00000010; // Enable Compare match interrupt (A), and Overflow Interrupt
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

// Don't need overflow in Fast PWM mode
// Further, our period is perfect for 1 ms. 

// int TimerOverflow = 0;

// ISR(TIMER0_OVF_vect)
// {
// 	TimerOverflow++;	/* Increment Timer Overflow count */
// 	Debug_PrintLine("Timer Overflow: %d", TimerOverflow);
// }
