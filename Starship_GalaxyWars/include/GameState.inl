#pragma once

#include "GameState.h"
#include "Fly.h"

GameState::GameState()
{
	m_enemies = new Enemy*[K_MAX_ENEMIES];
}

GameState& GameState::Get()
{
	static GameState m_instance;
	if(!m_instance.m_initialized) {m_instance.Initialize();}

	return m_instance;
}

void GameState::Initialize()
{
	m_numEnemies = K_MAX_ENEMIES;

	// Spawn Enemies
	for (int i = 0; i < K_MAX_ENEMIES; i++)
	{
		Fly* newEnemy = new Fly();
		m_enemies[i] = newEnemy;

		uint8_t dWidth = SCREEN_WIDTH / K_MAX_ENEMIES; // screen div for max enemies
		
		// Anchor point is top-left because this is early prototype. Or maybe i wont care at all.
		newEnemy->SetPosition(dWidth / 2 - (newEnemy->GetWidth() / 2) + (dWidth * i), 10);
	}

	m_initialized = true;
}
