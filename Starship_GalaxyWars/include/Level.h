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
	DoneReason_GameOverVictory,
	DoneReason_GameOverDefeat,
	DoneReason_StartGame,
	DoneReason_ViewHighScore,
};

struct Level
{
public:
	Level();
	virtual void Update();
	virtual void Render();
	virtual DoneReason GetDoneReason() = 0;
public:
	LevelType  m_type;
	bool       m_initialized = false;
};
