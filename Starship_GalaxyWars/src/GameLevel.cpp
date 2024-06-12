#include "GameLevel.h"
#include "GameState.h"
#include "ST7735SClient.h"
#include "Player.h"
#include "Bullet.h"
#include "TimerISR.h"
#include "Crab.h"
#include "Fly.h"
#include <string.h>
#include <stdlib.h>

GameLevel::GameLevel(EntityType* enemiesArray, uint8_t numEnemies, uint8_t level)
{
    Debug_PrintLine("GameLevel::GameLevel()");
	m_type = LevelType_Game;
    m_level = level;

    m_bullets = new Bullet*[K_MAX_BULLETS];
    m_numBullets = 0;

    InitializeEnemiesFromTypeArray(enemiesArray, numEnemies);

    m_player = new Player();
    m_player->SetPosition((SCREEN_WIDTH / 2) - (m_player->GetWidth() / 2), SCREEN_HEIGHT - BOTTOM_HUD_HEIGHT - m_player->GetHeight() - 1);
    m_player->SetInitialized();

    m_scoreText = new TextRenderObject();
    m_scoreText->SetPosition(5, 1);
    m_scoreText->SetInitialized();

    m_livesText = new TextRenderObject();

    char text[11];
    sprintf(text, "Lives: %d", m_player->GetHP());
    m_livesText->SetText(text);
    m_livesText->SetPosition(0, SCREEN_HEIGHT - m_livesText->GetHeight());
    m_livesText->SetInitialized();
}

GameLevel::~GameLevel()
{
    if(m_player) delete m_player;
    if(m_scoreText) delete m_scoreText;
    if(m_livesText) delete m_livesText;

    for(int i = 0; i < m_numBullets; i++)
    {
        delete m_bullets[i];
    }

    delete m_bullets;

    for(int i = 0; i < m_numEnemies; i++)
    {
        delete m_enemies[i];
    }

    delete m_enemies;
}

void GameLevel::InitializeEnemiesFromTypeArray(EntityType* enemyArray, uint8_t numEnemies)
{
    if(numEnemies <= 0)
    {
        // TODO(Darrell): Debug log message - game level empty enemies array
        return;
    }

    m_numEnemies = numEnemies;
    m_enemies = new Enemy*[numEnemies];

    uint8_t yStart = 15;
    uint8_t minSlotWidth = 25;
    uint8_t enemiesPerRow = min((SCREEN_WIDTH - 2) / minSlotWidth, numEnemies);
    uint8_t slotWidth = max(minSlotWidth, (SCREEN_WIDTH - 2) / numEnemies);
    uint8_t rowLeftOverAmt = numEnemies % enemiesPerRow;

    // Go through each entity type and lay them out on the screen 1 by 1.
    for (uint8_t i = 0; i < numEnemies; i++)
    {
        m_enemies[i] = CreateEnemyFromType(enemyArray[i]);

        // Set initial position of the enemy. 
        // We'll just lay them out side by side in rows

        uint8_t numLeftOver = numEnemies - i;
        if(rowLeftOverAmt > 0 && i >= 5)
        {
            for(uint8_t j = i; j < numEnemies; j++)
            {
                m_enemies[j] = CreateEnemyFromType(enemyArray[j]);
            }

            // Last row can't fill all slots, so we'll have special cases for them
            // assume can't have more than 5. (fly enemy is max 5)

            // I know this is SHIT code. The WORST code. DISGUSTING
            // ... but i got like 2 days before deadline and there's more important goals.
            if(numLeftOver == 1)
            {
                uint8_t xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (2 * slotWidth);
                uint8_t yPos = yStart + ((i / enemiesPerRow) * slotWidth);
                m_enemies[i]->SetPosition(xPos, yPos);
            }
            else if(numLeftOver == 2)
            {
                uint8_t xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (1 * slotWidth);
                uint8_t yPos = yStart + ((i / enemiesPerRow) * slotWidth);
                m_enemies[i]->SetPosition(xPos, yPos);

                xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (3 * slotWidth);
                m_enemies[i + 1]->SetPosition(xPos, yPos);
            }
            else if(numLeftOver == 3)
            {
                uint8_t xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (0 * slotWidth);
                uint8_t yPos = yStart + ((i / enemiesPerRow) * slotWidth);
                m_enemies[i]->SetPosition(xPos, yPos);

                xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (2 * slotWidth);
                m_enemies[i + 1]->SetPosition(xPos, yPos);

                xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (4 * slotWidth);
                m_enemies[i + 2]->SetPosition(xPos, yPos);
            }
            else if(numLeftOver == 4)
            {
                uint8_t xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (0 * slotWidth);
                uint8_t yPos = yStart + ((i / enemiesPerRow) * slotWidth);
                m_enemies[i]->SetPosition(xPos, yPos);

                xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (1 * slotWidth);
                m_enemies[i + 1]->SetPosition(xPos, yPos);

                xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (3 * slotWidth);
                m_enemies[i + 2]->SetPosition(xPos, yPos);

                xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (4 * slotWidth);
                m_enemies[i + 3]->SetPosition(xPos, yPos);
            }

            break; // we handled all cases here
        }
        else
        {
            uint8_t xPosIdx = i % enemiesPerRow;
            uint8_t xPos = 3 + (slotWidth / 2) - (m_enemies[i]->GetWidth() / 2) + (xPosIdx * slotWidth);

            uint8_t yPosIdx = i / enemiesPerRow;
            uint8_t yPos = yStart + (yPosIdx * slotWidth);

            m_enemies[i]->SetPosition(xPos, yPos);
        }
    }

    for(uint8_t i = 0; i < m_numEnemies; i++)
    {
        m_enemies[i]->UpdateIdlePositions();
        m_enemies[i]->SetInitialized();
        m_enemies[i]->UpdateLastMoveTime();
    }
}

Enemy* GameLevel::CreateEnemyFromType(EntityType type)
{
    switch(type)
    {
        case EntityType_Fly: return new Fly(); break;
	    case EntityType_GreenMonster: // TODO
	    case EntityType_Crab: return new Crab();
        default: return nullptr;
    }

    return nullptr;
}

void GameLevel::AddBullet(Bullet* newBullet)
{
	m_bullets[m_numBullets] = newBullet;
	m_numBullets++;
}

void GameLevel::DeleteBullet(uint8_t bulletIdx)
{
	if(m_numBullets <= bulletIdx) return;

	delete m_bullets[bulletIdx];
	m_bullets[bulletIdx] = m_bullets[m_numBullets - 1];
	m_numBullets--;
}

void GameLevel::DeleteEnemy(uint8_t enemyIdx)
{
	if(m_numEnemies <= enemyIdx) return;

	delete m_enemies[enemyIdx];
	m_enemies[enemyIdx] = m_enemies[m_numEnemies - 1];
	m_numEnemies--;
}

void GameLevel::Update()
{
    GameState& gameState = GameState::Get();

    if(!m_initialized)
    {
        UpdateScoreText(gameState.m_score);
        m_initialized = true;
    }

    if(m_doneReason != DoneReason_None)
    {
        return;
    }

    // Update Gamestate with Input
    if(gameState.m_fireButton && 
      (gameState.m_timeSinceLastFireMS >= gameState.m_timeNextFireMS) && m_numBullets < K_MAX_BULLETS)
    {
        gameState.m_timeSinceLastFireMS = 0;
        gameState.m_timeNextFireMS = K_PLAYER_BULLET_FIREINTERVAL;

        Bullet* newBullet = new Bullet(BulletType_PlayerNormal);
        XYCoord spawnPos = m_player->GetPosition();
        spawnPos.m_x += (m_player->GetWidth() / 2) - 1;
        spawnPos.m_y -= 5;
        newBullet->SetPosition(spawnPos);
        newBullet->SetInitialized();
        AddBullet(newBullet);
    }
    else
    {
        gameState.m_timeSinceLastFireMS += gameState.m_deltaTimeMS;
    }

    // Update Moving Entities
        // Player
        if(gameState.m_joystickDirectionX != JD_CENTER)
        {
            Player* player = m_player;
            float dX = (float)K_PLAYER_SPEED * gameState.m_deltaTimeMS;
            XYCoord currentPosition = player->GetPosition();

            if(gameState.m_joystickDirectionX == JD_LEFT)
            {
                dX *= -1;
            }
            
            player->SetPosition(currentPosition.m_x + dX, currentPosition.m_y);
        }

        // Bullets
        for(uint8_t bIdx = 0; bIdx < m_numBullets; bIdx++)
        {
            Bullet* bullet = m_bullets[bIdx];
            float dY = (float)K_BULLET_SPEED * gameState.m_deltaTimeMS;
            XYCoord currentPosition = bullet->GetPosition();

            if(bullet->GetType() == BulletType_EnemyNormal)
            {
                dY *= -1;
            }

            // Check for entity collision
            for(uint8_t eIdx = 0; eIdx < m_numEnemies; eIdx++)
            {	
                Enemy* enemy = m_enemies[eIdx];
                if(!bullet->GetIsMarkedForDeletion() && bullet->GetType() == BulletType_PlayerNormal && bullet->GetCollides(*enemy))
                {
                    enemy->TakeDamage(1);
                    if(!enemy->GetIsAlive())
                    {
                        enemy->SetIsMarkedForDeletion(true);
                        gameState.m_score += enemy->GetScoreValue();
                        UpdateScoreText(gameState.m_score);
                    }
                    bullet->SetIsMarkedForDeletion(true);
                }
                else if(!bullet->GetIsMarkedForDeletion() && bullet->GetType() == BulletType_EnemyNormal && bullet->GetCollides(*m_player))
                {
                    m_player->TakeDamage(1);

                    char text[11];
                    sprintf(text, "Lives: %d", m_player->GetHP());
                    m_livesText->SetText(text);

                    if(!m_player->GetIsAlive())
                    {
                        switch(m_level)
                        {
                            case 1:
                                m_doneReason = DoneReason_Lvl1GameOverDefeat;
                                break;
                            case 2:
                                m_doneReason = DoneReason_Lvl2GameOverDefeat;
                                break;
                        }
                    }
                    bullet->SetIsMarkedForDeletion(true);
                }
            }

            // Check if bullet is out of play area
            if (!bullet->GetIsMarkedForDeletion())
            {
                if(currentPosition.m_y <= TOP_HUD_HEIGHT || currentPosition.m_y - dY >= SCREEN_HEIGHT - TOP_HUD_HEIGHT)
                {
                    bullet->SetIsMarkedForDeletion(true);
                }
                else
                {
                    bullet->SetPosition(currentPosition.m_x, currentPosition.m_y - dY);
                }
            }

            
        }

        // Enemies
        for(int x = 0; x < m_numEnemies; x++)
        {
            Enemy* enemy = m_enemies[x];

            XYCoord desiredPosition = enemy->GetDesiredPos();
            XYCoord currentPosition = enemy->GetPosition();
            //Debug_PrintLine("current x: %d, desired x: %d", currentPosition.m_x, desiredPosition.m_x);
            double  enemyIdleSpeed = 0.1;
            uint8_t newX = 0;

            enemy->UpdateDesiredPosition();
            if(!enemy->GetMoveDebtPaid(enemyIdleSpeed))
            {
                enemy->UpdateMoveTimeDebt(gameState.m_deltaTimeMS);
                continue;
            }

            if(desiredPosition.m_x < currentPosition.m_x)
            {
                newX = clamp(currentPosition.m_x - 1, desiredPosition.m_x, currentPosition.m_x);
                enemy->SetPosition(newX, currentPosition.m_y);
            }
            else
            {
                
                newX = clamp(currentPosition.m_x + 1, currentPosition.m_x, desiredPosition.m_x);
                enemy->SetPosition(newX, currentPosition.m_y);
            }

            enemy->UpdateLastMoveTime();

            // Enemy shooting
            uint32_t tNow = gameState.m_lastFrameTimeMS + gameState.m_deltaTimeMS;
            uint32_t timeSinceLastFire = (tNow - enemy->m_timeLastFire);
            m_timeSinceLastEnemyFire += gameState.m_deltaTimeMS;
            if(timeSinceLastFire >= 450 && m_timeSinceLastEnemyFire >= 100 && m_numBullets < K_MAX_BULLETS)
            {
                Bullet* newBullet = new Bullet(BulletType_EnemyNormal);
                XYCoord spawnPos = enemy->GetPosition();
                spawnPos.m_x += (enemy->GetWidth() / 2) - 1;
                spawnPos.m_y += enemy->GetHeight() + 5;
                newBullet->SetPosition(spawnPos);
                newBullet->SetInitialized();
                AddBullet(newBullet);

                enemy->m_timeLastFire = gameState.m_lastFrameTimeMS + gameState.m_deltaTimeMS;
                m_timeSinceLastEnemyFire = 0;
            }
        }


    // Delete to-be-deleted entities
    
    // Bullets
    for(uint8_t i = 0; i < m_numBullets; i++)
    {
        Bullet* bullet = m_bullets[i];
        if(bullet->GetIsMarkedForDeletion())
        {
            DeleteBullet(i);
            i -= 1;
        }
    }

    // Enemies
    for(uint8_t i = 0; i < m_numEnemies; i++)
    {
        Enemy* enemy = m_enemies[i];
        if(enemy->GetIsMarkedForDeletion())
        {
            DeleteEnemy(i);
            i -= 1;
        }
    }

    if(m_numEnemies <= 0)
    {
        switch(m_level)
        {
            case 1:
                m_doneReason = DoneReason_Lvl1GameOverVictory;
                break;
            case 2:
                m_doneReason = DoneReason_Lvl2GameOverVictory;
                break;
        }
    }
}

void GameLevel::Render()
{
    m_scoreText->Render();
    m_livesText->Render();
    
	for(int i = 0; i < m_numEnemies; i++)
	{
		Enemy* enemy = m_enemies[i];
		enemy->Render();
	}

	m_player->Render();

	for(int i = 0; i < m_numBullets; i++)
	{
		Bullet* bullet = m_bullets[i];
		bullet->Render();
	}
}

void GameLevel::UpdateScoreText(uint8_t newScore)
{
    char buffer[8] = "Score: ";
    char bufferNum[3];
    char result[11];
    strcpy(result, strcat(buffer, itoa(newScore, bufferNum, 10))); 
    m_scoreText->SetText(result);
}

DoneReason GameLevel::GetDoneReason()
{
    return m_doneReason;
}
