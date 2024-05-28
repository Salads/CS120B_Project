#include "Tasks/Tasks.h"
#include "ScreenRegion.h"
#include "GameState.h"
#include "Bullet.h"

int Tick_Render(int state)
{
	switch(state) // transitions
	{
		case TS_RENDER_INIT: state = TS_RENDER_DORENDER; break;
		case TS_RENDER_DORENDER: break;
		default: break;
	}

	switch(state) // state actions
	{
		case TS_RENDER_INIT: break;
		case TS_RENDER_DORENDER:
		{
			GameState& gameState = GameState::Get();
			gameState.m_currentLevel->Render();

		} break;
		default: break;
	}

	return state;
}
