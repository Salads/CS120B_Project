#include "GameLevel.h"
#include "GameState.h"
#include "ST7735SClient.h"

GameLevel::GameLevel(EntityType* enemiesArray, uint8_t numEnemies)
{
	m_type = LevelType_Game;

    m_bullets = new Bullet*[K_MAX_BULLETS];
    m_numBullets = 0;

    InitializeEnemiesFromTypeArray(enemiesArray, numEnemies);

    m_player = new Player();
    m_player->SetPosition((SCREEN_WIDTH / 2) - (m_player->GetWidth() / 2), SCREEN_HEIGHT - BOTTOM_HUD_HEIGHT - m_player->GetHeight() - 1);
    m_player->SetRenderDirty(true);

    Debug_PrintLine("Player Start Pos: %d, %d", m_player->GetPosition().m_x, m_player->GetPosition().m_y);

    m_guiScoreLabel = new GUIItem(&kTextTextureScore);
    m_guiScoreLabel->SetPosition(2, 0);

    m_initialized = true;
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

    Debug_PrintLine("# Enemies: %d", m_numEnemies);

    uint8_t yStart = 15;
    uint8_t minSlotWidth = 25;
    uint8_t enemiesPerRow = min((SCREEN_WIDTH - 2) / minSlotWidth, numEnemies);
    uint8_t slotWidth = max(minSlotWidth, (SCREEN_WIDTH - 2) / numEnemies);

    uint8_t rowsBeforeLeftover = numEnemies / enemiesPerRow;
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
}

Enemy* GameLevel::CreateEnemyFromType(EntityType type)
{
    switch(type)
    {
        case EntityType_Fly: return new Fly(); break;
	    case EntityType_GreenMonster: // TODO
	    case EntityType_Crab: // TODO
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

    // Update Gamestate with Input
    if(gameState.m_fireButton && 
        (gameState.m_timeSinceLastFireMS >= K_PLAYER_BULLET_FIREINTERVAL) &&
            m_numBullets < K_MAX_BULLETS)
    {
        gameState.m_timeSinceLastFireMS = 0;

        Bullet* newBullet = new Bullet(BulletType_PlayerNormal);
        XYCoord spawnPos = m_player->GetPosition();
        spawnPos.m_x += (m_player->GetWidth() / 2) - 1;
        spawnPos.m_y -= 5;
        newBullet->SetPosition(spawnPos);
        AddBullet(newBullet);
        
    }
    else
    {
        gameState.m_timeSinceLastFireMS += gameState.m_deltaTimeMS;
    }

    // Update Moving Entities
        // Player
        if(gameState.m_joystickDirection != JD_CENTER)
        {
            Player* player = m_player;
            float dX = (float)K_PLAYER_SPEED * gameState.m_deltaTimeMS;
            XYCoord currentPosition = player->GetPosition();

            if(gameState.m_joystickDirection == JD_LEFT)
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

            // Check for entity collision
            for(uint8_t eIdx = 0; eIdx < m_numEnemies; eIdx++)
            {	
                Enemy* enemy = m_enemies[eIdx];
                if(bullet->GetCollides(*enemy))
                {
                    enemy->SetIsMarkedForDeletion(true);
                    bullet->SetIsMarkedForDeletion(true);
                    gameState.m_score += enemy->GetScoreValue();
                    //Debug_PrintLine("New Score: %d", gameState.m_score);
                }
            }

            // Check if bullet is out of play area
            if (!bullet->GetIsMarkedForDeletion())
            {
                if(currentPosition.m_y <= TOP_HUD_HEIGHT || currentPosition.m_y - dY <= TOP_HUD_HEIGHT)
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
        static bool b = true;
        for (uint8_t i = 0; i < m_numEnemies; i++)
        {
            Enemy* enemy = m_enemies[i];
            uint8_t mul = (b ? 1 : -1);
            XYCoord curPos = enemy->GetPosition();
            curPos.m_x = curPos.m_x + (mul * 5);
            enemy->SetPosition(curPos);
        }
        b = !b;


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
}

void GameLevel::Render()
{
	ST7735SClient& renderer = ST7735SClient::Get();
	for(int i = 0; i < m_numEnemies; i++)
	{
		Enemy* enemy = m_enemies[i];
		if(enemy->GetRenderDirty())
		{
			renderer.RenderEntity(enemy);
			enemy->SetRenderDirty(false);
		}
	}

	if(m_player->GetRenderDirty())
	{
		renderer.RenderEntity(m_player);
		m_player->SetRenderDirty(false);
	}

	for(int i = 0; i < m_numBullets; i++)
	{
		Bullet* bullet = m_bullets[i];
		if(bullet->GetRenderDirty())
		{
			renderer.RenderEntity(bullet, false);
			bullet->SetRenderDirty(false);
		}
	}

    if(m_guiScoreLabel->GetRenderDirty())
    {
        renderer.RenderEntity(m_guiScoreLabel, false);
        m_guiScoreLabel->SetRenderDirty(false);
    }
}
