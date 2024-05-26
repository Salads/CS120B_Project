#include "SerialMonitor.h"

void Serial_Init(int baud)
{
	UBRR0 = (((16000000 / (baud * 16UL))) - 1); // Set baud rate
	UCSR0B |= (1 << TXEN0);
	UCSR0B |= (1 << RXEN0);
	UCSR0B |= (1 << RXCIE0);
	UCSR0B &= ~(1 << RXCIE0);
	UCSR0C = (3 << UCSZ00);
}

// sends a char
void Serial_PrintChar(char ch)
{
	while ((UCSR0A & (1 << UDRE0)) == 0);
	UDR0 = ch;
}

void Serial_Print(char *str)
{
	for (int i; str[i] != '\0'; i++)
	{
		Serial_PrintChar(str[i]);
	}
}

// sends a string
void Serial_PrintLine(char *str)
{
	for (int i; str[i] != '\0'; i++)
	{
		Serial_PrintChar(str[i]);
	}
	Serial_PrintChar('\n');
}

// sends an long. can be used with integers
void Serial_PrintLine(long num, int base)
{
	char arr[sizeof(long) * 8 + 1];	   // array with size of largest possible number of digits for long
	char *str = &arr[sizeof(arr) - 1]; // point to last val in buff
	*str = '\0';					   // set last val in buff to null terminator

	if (num < 0) // if negative, print '-' and turn n to positive
	{ 
		Serial_PrintChar('-');
		num = -num;
	}

	if (num == 0) // if 0, print 0
	{
		Serial_PrintChar(48);
	}
	else // else, fill up arr starting from the last number
	{
		while (num)
		{
			char temp = num % base;							 // get digit
			num /= base;									 // shift to next digit
			str--;											 // go back a spot in arr
			*str = temp < 10 ? temp + '0' : temp + 'A' - 10; // "+ A - 10" for A-F hex vals
		}
	}

	Serial_PrintLine(str); // print from str to end of arr
}
