#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Defines.h"

// TODO(Darrell): something like printf? 
// TODO(Darrell): Macro magic to take out serial monitor printing? (it's slow)

FORCE_INLINE void Serial_Init(int baud);
FORCE_INLINE void Serial_PrintChar(char ch);
FORCE_INLINE void Serial_Print(char *str);
FORCE_INLINE void Serial_PrintLine(char *str);
FORCE_INLINE void Serial_PrintLine(long num, int base = 10);

#include "SerialMonitor.inl"
