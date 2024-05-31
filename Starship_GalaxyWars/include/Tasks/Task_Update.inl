#include "Tasks/Tasks.h"
#include "GameState.h"
#include "Bullet.h"
#include "Utility.h"

int Tick_Update(int state)
{
	switch(state)
	{
		case TS_UPDATE_INIT: state = TS_UPDATE_DOUPDATE; break;
		case TS_UPDATE_DOUPDATE: break;
		default: break;
	}

	switch (state)
	{
	case TS_UPDATE_INIT: break;
	case TS_UPDATE_DOUPDATE: 
	{
		GameState& gameState = GameState::Get();
		gameState.m_currentLevel->Update();
		if(gameState.m_currentLevel->GetDoneReason() == DoneReason_StartGame ||
			gameState.m_currentLevel->GetDoneReason() == DoneReason_ViewHighScore) // TODO(Darrell): High score level.
		{
			delete gameState.m_currentLevel;
			gameState.m_currentLevel = new GameLevel(kLevel1Enemies, kNumLevel1Enemies);
		}

	} break;
	default: break;
	}

	return state;
}
