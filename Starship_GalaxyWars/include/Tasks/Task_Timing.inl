#include "Tasks/Tasks.h"
#include "GameState.h"

int Tick_Timing(int state)
{
	switch(state)
	{
		case TS_TIMING_INIT: state = TS_TIMING_UPDATE; break;
		case TS_TIMING_UPDATE: break;
		default: break;
	}

	switch (state)
	{
	case TS_TIMING_INIT: break;
	case TS_TIMING_UPDATE:
	{
		GameState::Get().UpdateDeltaTime();
	} break;
	default: break;
	}

	return state;
}
