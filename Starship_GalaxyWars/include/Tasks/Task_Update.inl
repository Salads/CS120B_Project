#include "Tasks/Tasks.h"
#include "GameState.h"
#include "Bullet.h"
#include "Utility.h"
#include "EndScreenLevel.h"
#include "MainMenuLevel.h"
#include "DebugLevel_ScreenSize.h"
#include "DebugLevel_Region.h"

Level* GetNextLevel(DoneReason completeReason)
{
	Level* newLevel;
	switch(completeReason)
	{
		case DoneReason_None:
			newLevel = new MainMenuLevel(); 
			break;
		case DoneReason_StartGame:
		case DoneReason_ViewHighScore:
			newLevel = new GameLevel(kLevel1Enemies, kNumLevel1Enemies);
			break;
		case DoneReason_GameOverVictory:
		case DoneReason_GameOverDefeat:
			newLevel = new EndScreenLevel();
			break;
		case DoneReason_EndScreenDone:
			// If I don't put this here, this gets optimized out when we go from end screen to main menu. siiiiiigh
			// It can't be an empty string either. SIIIIIIIGH
			Debug_PrintLine("Level Cycle done! Reset to main menu...");
			newLevel = new MainMenuLevel();
			break;
		default:
			break;
	}

	return newLevel;
}

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
		if(gameState.m_currentLevel == nullptr)
		{
			#if DEBUG_SCREENSIZE
				gameState.m_currentLevel = new DebugLevel_ScreenSize();
			#elif DEBUG_REGIONS
				gameState.m_currentLevel = new DebugLevel_Region();
			#else
				gameState.m_currentLevel = new MainMenuLevel();
			#endif
		}

		gameState.m_currentLevel->Update();

		DoneReason currentDoneReason = gameState.m_currentLevel->GetDoneReason();
		if (currentDoneReason != DoneReason_None)
		{
			delete gameState.m_currentLevel;
			gameState.m_currentLevel = GetNextLevel(currentDoneReason);
		}

	} break;
	}

	return state;
}
