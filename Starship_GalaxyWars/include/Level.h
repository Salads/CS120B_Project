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
	DoneReason_MenuOption1,
	DoneReason_MenuOption2,
	DoneReason_MenuOption3,
	DoneReason_MenuOption4
};

struct Level
{
public:
	virtual void Update();
	virtual void Render();
	virtual DoneReason GetDoneReason();
public:
	LevelType m_type;
	bool      m_initialized = false;
};
