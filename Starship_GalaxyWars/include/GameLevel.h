#pragma once

#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

struct GameLevel : public Level
{
public:
	GameLevel();
	void Update();
	void Render();

private:
	void UpdateEnemies();
	void UpdateBullets();

public:
	Player*  m_player;

	Enemy**  m_enemies;
	uint8_t  m_numEnemies = 0;

	Bullet** m_bullets;
	uint8_t  m_numBullets = 0;

	bool     m_isGameOver = false;

	
};
