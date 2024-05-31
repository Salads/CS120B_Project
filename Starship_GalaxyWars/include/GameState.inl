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

// This works on Timer2 (interrupts on 1ms), which (i think) has a cpu time of 
// 16Mhz, which translates to an oscillation interavl of 60 something fractional
// nanoseconds. This means it's possible that a ms value happens in real life, but not 
// our timer. But, the hope is that we don't need necessarily a exactly precise ms.
void GameState::UpdateDeltaTime()
{
	uint32_t timePassedMS = 0;
	uint32_t currentTimeMS = GetTimeMS();
	// timeMS has overflown, so we'll 
	if (m_lastFrameTimeMS > currentTimeMS)
	{
		uint32_t leftOver = UINT32_MAX - m_lastFrameTimeMS;
		timePassedMS = leftOver + currentTimeMS;
	}
	else
	{
		timePassedMS = currentTimeMS - m_lastFrameTimeMS;
	}

	m_deltaTimeMS = timePassedMS;
	m_lastFrameTimeMS = currentTimeMS;
}

void GameState::Initialize()
{
	Debug_PrintLine("GameState Initialize");
	m_initialized = true;
}
