#pragma once

#include <stdint.h>

enum LevelType : uint8_t
{
	LevelType_None, // Not initialized! Error!
	LevelType_Menu,
	LevelType_Game
};

enum DoneReason : uint8_t
{
	DoneReason_None,
	DoneReason_Lvl1GameOverVictory,
	DoneReason_Lvl1GameOverDefeat,
	DoneReason_Lvl2GameOverVictory,
	DoneReason_Lvl2GameOverDefeat,
	DoneReason_StartGame,
	DoneReason_ViewHighScore,
	DoneReason_HighScore_GoBack,
	DoneReason_EndScreenDone,

	DoneReason_Unknown
};

struct Level
{
public:
	Level();
	virtual ~Level();
	virtual void Update();
	virtual void Render();
	virtual DoneReason GetDoneReason() = 0;
public:
	LevelType  m_type;
	bool       m_initialized = false;
};
