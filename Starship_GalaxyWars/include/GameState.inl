#pragma once

#include "GameState.h"

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
		Enemy* newEnemy = new Enemy();
		m_enemies[i] = newEnemy;
		
		// This isn't tied with anything, just for first demo purposes
		// Display Res: 128x160
		// Anchor point is top-left because this is early prototype. Or maybe i wont care at all.
		if(i == 0)
		{
			newEnemy->SetPosition(0 + 32 + 10, 20);
		}
		if(i == 1)
		{
			newEnemy->SetPosition(128 - 32 - 10, 20);
		}
	}

	m_initialized = true;
}
