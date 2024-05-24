#include "Tasks.h"
#include "ST7735SClient.h"
#include "JoystickDirection.h"

int Tick_Render(int state)
{
	switch(state) // transitions
	{
		case TS_RENDER_INIT: state = TS_RENDER_DORENDER; break;
		case TS_RENDER_DORENDER: break;
	}

	switch(state) // state actions
	{
		case TS_RENDER_INIT: break;
		case TS_RENDER_DORENDER:
		{

		} break;
	}

	return state;
}

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
		
	} break;
	default: break;
	}

	return state;
}
