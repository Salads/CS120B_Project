#include "Tasks/Tasks.h"
#include "GameState.h"
#include "Bullet.h"
#include "Utility.h"
#include "EndScreenLevel.h"
#include "MainMenuLevel.h"
#include "DebugLevel_ScreenSize.h"
#include "DebugLevel_Region.h"
#include "HighScoreLevel.h"

Level* GetNextLevel(DoneReason completeReason)
{
	Level* newLevel;
	switch(completeReason)
	{
		case DoneReason_None:
			newLevel = new MainMenuLevel(); 
			break;
		case DoneReason_StartGame:
			newLevel = new GameLevel(kLevel1Enemies, kNumLevel1Enemies, 1);
			break;
		case DoneReason_ViewHighScore:
			newLevel = new HighScoreLevel();
			break;
		case DoneReason_Lvl1GameOverVictory:
			newLevel = new GameLevel(kLevel2Enemies, kNumLevel2Enemies, 2);
			break;
		case DoneReason_Lvl1GameOverDefeat:
		case DoneReason_Lvl2GameOverVictory:
		case DoneReason_Lvl2GameOverDefeat:
			newLevel = new EndScreenLevel(completeReason);
			break;
		case DoneReason_EndScreenDone:
		case DoneReason_HighScore_GoBack:
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
