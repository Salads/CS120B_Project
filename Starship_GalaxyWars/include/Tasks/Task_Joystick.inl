#include "Tasks/Tasks.h"
#include "JoystickDirection.h"
#include "Periph.h"

int Tick_Joystick(int state)
{
	switch(state)
	{
		case TS_JOYSTICK_INIT: state = TS_JOYSTICK_SAMPLE; break;
		case TS_JOYSTICK_SAMPLE: break;
		default: break;
	}

	switch (state)
	{
	case TS_JOYSTICK_INIT: break;
	case TS_JOYSTICK_SAMPLE:
	{
		GameState& gameState = GameState::Get();
		uint32_t joystickValue = ReadADC(0);
		if(joystickValue < 350) {gameState.m_joystickDirection = JD_LEFT;}
		else if(joystickValue > 700) {gameState.m_joystickDirection = JD_RIGHT;}
		else {gameState.m_joystickDirection = JD_CENTER;}

	} break;
	default: break;
	}

	return state;
}
