#pragma once

// Permission to copy is granted provided that this header remains intact. 
// This software is provided with no warranties.

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Defines.h"

void TimerISR(void);

void TimerSet(unsigned long M);
void TimerOn();
void TimerOff();
