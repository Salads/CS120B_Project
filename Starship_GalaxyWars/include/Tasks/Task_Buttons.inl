#include "Tasks/Tasks.h"
#include "GameState.h"

int Tick_Buttons(int state)
{
	switch(state)
	{
		case TS_BUTTONS_INIT: state = TS_BUTTONS_SAMPLE; break;
		case TS_BUTTONS_SAMPLE: break;
		default: break;
	}

	switch (state)
	{
	case TS_BUTTONS_INIT: break;
	case TS_BUTTONS_SAMPLE:
	{
		// [0-7] PORTD (8bit)
		// [8-13] PORTB (6bit)
		// [A0-A5] PORTC (6bit)
		// Output: DDR=1, PORT=0
		// PINx: Read Input
		// PORTx: Set Output

		bool isButtonDown = GetBit(PIND, PIND7);
		GameState::Get().m_fireButton = isButtonDown;

	} break;
	default: break;
	}

	return state;
}