#pragma once

#include <avr/io.h>

#include "GameState.h"
#include "Fly.h"
#include "Player.h"
#include "SerialMonitor.h"
#include "LevelConfig.h"
#include "TimerISR.h"

GameState::GameState()
{
	m_currentLevel = new GameLevel(kLevel1Enemies, kNumLevel1Enemies);
}

GameState& GameState::Get()
{
	static GameState m_instance;
	if(!m_instance.m_initialized) {m_instance.Initialize();}

	return m_instance;
}

// Since we store a u32 for ms time, we have ~49 days worth of 
// constant gametime before overflow could become an issue.
// I'll just leave it at that, no need to be perfect here.
void GameState::UpdateDeltaTime()
{
	uint32_t timePassedMS = 0;
	uint32_t currentTimeMS = GetTimeMS();
	m_deltaTimeMS = currentTimeMS - m_lastFrameTimeMS;
	m_lastFrameTimeMS = currentTimeMS;
}

void GameState::Initialize()
{
	Debug_PrintLine("GameState Initialize");
	m_initialized = true;
}
