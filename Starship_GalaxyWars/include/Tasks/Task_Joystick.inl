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
		if(joystickValue < 350) {gameState.m_joystickDirectionX = JD_LEFT;}
		else if(joystickValue > 700) {gameState.m_joystickDirectionX = JD_RIGHT;}
		else {gameState.m_joystickDirectionX = JD_CENTER;}

		joystickValue = ReadADC(1);
		if(joystickValue < 350) {gameState.m_joystickDirectionY = JD_DOWN;}
		else if(joystickValue > 700) {gameState.m_joystickDirectionY = JD_UP;}
		else {gameState.m_joystickDirectionY = JD_CENTER;}

	} break;
	default: break;
	}

	return state;
}
