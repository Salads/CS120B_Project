#include "Tasks.h"
#include "DisplayClient.h"

int Tick_Render(int state)
{
	static DisplayClient displayClient;

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
