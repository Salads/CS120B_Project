#pragma once

#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "TextRenderObject.h"

struct GameLevel : public Level
{
public:
	GameLevel(EntityType* enemiesArray, uint8_t numEnemiesm, uint8_t level);
	~GameLevel();
	void Update();
	void Render();

	void AddBullet(Bullet* newBullet);
    void DeleteBullet(uint8_t bulletIdx);
    void DeleteEnemy(uint8_t enemyIdx);
	Enemy* CreateEnemyFromType(EntityType type);
	void InitializeEnemiesFromTypeArray(EntityType* enemyArray, uint8_t numEnemies);
	DoneReason GetDoneReason();

private:
	void UpdateEnemies();
	void UpdateBullets();
	void UpdateScoreText(uint8_t newScore);

public:
	Player*   		  m_player;

	uint8_t			  m_level = 0;

	Enemy**   		  m_enemies;
	uint8_t   		  m_numEnemies = 0;

	Bullet**  		  m_bullets;
	uint8_t   		  m_numBullets = 0;
	uint32_t		  m_timeSinceLastEnemyFire = UINT32_MAX;

	TextRenderObject* m_scoreText;
	TextRenderObject* m_livesText;

	bool      		  m_isGameOver = false;
	bool			  m_initialized = false;
private:
	DoneReason 		  m_doneReason = DoneReason_None;
};