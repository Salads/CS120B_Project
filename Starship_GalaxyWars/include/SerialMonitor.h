#pragma once

#include "Defines.h"
#include <stdio.h>
#include <stdarg.h>

// TODO(Darrell): something like printf? 
// TODO(Darrell): Macro magic to take out serial monitor printing? (it's slow)

#define DEBUGPRINT_MAXCHARS 128
#define DEBUGPRINT_ENABLED false

void Debug_Print(const char* format, ...);
void Debug_PrintLine(const char* format, ...);
void Serial_Init(int baud);
void Serial_PrintChar(const char ch);
void Serial_Print(const char *str);
void Serial_PrintLine(const char *str);
void Serial_PrintLine(long num, int base = 10);
