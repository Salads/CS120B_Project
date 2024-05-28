#pragma once

#include <stdint.h>

enum LevelType : uint8_t
{
	LevelType_None, // Not initialized! Error!
	LevelType_Menu,
	LevelType_Game
};

struct Level
{
public:
	virtual void Update();
	virtual void Render();
public:
	LevelType m_type;
};
