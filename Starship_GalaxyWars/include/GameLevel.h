#pragma once

#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "TextRenderObject.h"

struct GameLevel : public Level
{
public:
	GameLevel(EntityType* enemiesArray, uint8_t numEnemies);
	void Update();
	void Render();

	void AddBullet(Bullet* newBullet);
    void DeleteBullet(uint8_t bulletIdx);
    void DeleteEnemy(uint8_t enemyIdx);
	Enemy* CreateEnemyFromType(EntityType type);
	void InitializeEnemiesFromTypeArray(EntityType* enemyArray, uint8_t numEnemies);

private:
	void UpdateEnemies();
	void UpdateBullets();
	void UpdateScoreText(uint8_t newScore);

public:
	Player*   		  m_player;

	Enemy**   		  m_enemies;
	uint8_t   		  m_numEnemies = 0;

	Bullet**  		  m_bullets;
	uint8_t   		  m_numBullets = 0;

	TextRenderObject* m_scoreText;

	bool      		  m_isGameOver = false;
	bool			  m_initialized = false;
};