#pragma once

#include "GameState.h"
#include "Fly.h"
#include "Player.h"

GameState::GameState()
{
	m_enemies = new Enemy*[K_MAX_ENEMIES];
	m_bullets = new Bullet*[K_MAX_BULLETS];
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
double GameState::GetDeltaTime()
{
	double dtSeconds = 0.0;

	uint32_t timePassedMS = 0;
	// timeMS has overflown, so we'll 
	if (m_lastFrameMS > m_timeMS)
	{
		uint32_t leftOver = UINT32_MAX - m_lastFrameMS;
		timePassedMS = leftOver + m_timeMS;
	}
	else
	{
		timePassedMS = m_timeMS - m_lastFrameMS;
	}

	dtSeconds = timePassedMS * 1000;
	return dtSeconds;
}

void GameState::Initialize()
{
	m_numEnemies = K_MAX_ENEMIES;
	m_numBullets = 0;

	// Spawn Enemies
	for (int i = 0; i < K_MAX_ENEMIES; i++)
	{
		Fly* newEnemy = new Fly();
		m_enemies[i] = newEnemy;

		uint8_t dWidth = SCREEN_WIDTH / K_MAX_ENEMIES; // screen div for max enemies
		
		// Anchor point is top-left because this is early prototype. Or maybe i wont care at all.
		newEnemy->SetPosition(dWidth / 2 - (newEnemy->GetWidth() / 2) + (dWidth * i), 10);
	}

	m_player = new Player();
	m_player->SetPosition(64, 100);

	m_initialized = true;
}
