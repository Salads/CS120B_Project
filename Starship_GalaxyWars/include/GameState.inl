#pragma once

#include <avr/io.h>
#include <avr/eeprom.h>
#include "GameState.h"
#include "Fly.h"
#include "Player.h"
#include "SerialMonitor.h"
#include "LevelConfig.h"
#include "TimerISR.h"
#include "MainMenuLevel.h"
#include "DebugLevel_ScreenSize.h"

GameState::GameState()
{
	
}

void GameState::ClearHighScores()
{
	for(uint8_t i = 0; i < K_MAX_HIGHSCORES; i++)
	{
		eeprom_busy_wait();
		eeprom_write_byte((uint8_t*)0 + i, 0);
	}

	m_numScores = 0;
}

void GameState::LoadHighScores()
{
	m_numScores = 0;
	for(uint8_t i = 0; i < K_MAX_HIGHSCORES; i++)
	{
		eeprom_busy_wait();
		m_scores[i] = eeprom_read_byte((uint8_t*)0 + i);
		if(m_scores[i] > 0)
		{
			m_numScores++;
		}
	}
}

void GameState::SaveHighScores()
{
	for(uint8_t i = 0; i < K_MAX_HIGHSCORES; i++)
	{
		eeprom_busy_wait();
		eeprom_write_byte((uint8_t*)0 + i, m_scores[i]);
	}
}

void GameState::InsertScore(uint8_t newScore)
{
	for(uint8_t i = 0; i < K_MAX_HIGHSCORES; i++)
	{
        if (newScore > m_scores[i])
        {
			for(int x = K_MAX_HIGHSCORES - 1; x > i; x--)
			{
				m_scores[x] = m_scores[x - 1];
			}
            m_scores[i] = newScore;
			m_numScores = clamp(m_numScores + 1, 0, K_MAX_HIGHSCORES);
			return;
        }
	}
	
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
	uint32_t currentTimeMS = GetTimeMS();
	m_deltaTimeMS = currentTimeMS - m_lastFrameTimeMS;
	m_lastFrameTimeMS = currentTimeMS;
}

void GameState::Initialize()
{
	m_initialized = true;
}
