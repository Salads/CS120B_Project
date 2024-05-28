#include "Tasks/Tasks.h"
#include "GameState.h"
#include "Bullet.h"
#include "Utility.h"

int Tick_Update(int state)
{
	switch(state)
	{
		case TS_UPDATE_INIT: state = TS_UPDATE_DOUPDATE; break;
		case TS_UPDATE_DOUPDATE: break;
		default: break;
	}

	switch (state)
	{
	case TS_UPDATE_INIT: break;
	case TS_UPDATE_DOUPDATE: 
	{
		GameState& gameState = GameState::Get();

		// Update Gamestate with Input
		if(gameState.m_fireButton && 
			(gameState.m_timeSinceLastFireMS >= K_PLAYER_BULLET_FIREINTERVAL) &&
			 gameState.m_numBullets < K_MAX_BULLETS)
		{
			gameState.m_timeSinceLastFireMS = 0;

			Bullet* newBullet = new Bullet(BulletType_PlayerNormal);
			XYCoord spawnPos = gameState.m_player->GetPosition();
			spawnPos.m_x += (gameState.m_player->GetWidth() / 2) - 1;
			spawnPos.m_y -= 5;
			newBullet->SetPosition(spawnPos);
			gameState.AddBullet(newBullet);
			
		}
		else
		{
			gameState.m_timeSinceLastFireMS += gameState.m_deltaTimeMS;
		}

		// Update Moving Entities
			// Player
			if(gameState.m_joystickDirection != JD_CENTER)
			{
				Player* player = gameState.m_player;
				float dX = (float)K_PLAYER_SPEED * gameState.m_deltaTimeMS;
				XYCoord currentPosition = player->GetPosition();

				if(gameState.m_joystickDirection == JD_LEFT)
				{
					dX *= -1;
				}
				
				player->SetPosition(currentPosition.m_x + dX, currentPosition.m_y);
			}

			// Bullets
			for(uint8_t bIdx = 0; bIdx < gameState.m_numBullets; bIdx++)
			{
				Bullet* bullet = gameState.m_bullets[bIdx];
				float dY = (float)K_BULLET_SPEED * gameState.m_deltaTimeMS;
				XYCoord currentPosition = bullet->GetPosition();

				// Check for entity collision
				for(uint8_t eIdx = 0; eIdx < gameState.m_numEnemies; eIdx++)
				{	
					Enemy* enemy = gameState.m_enemies[eIdx];
					if(bullet->GetCollides(*enemy))
					{
						enemy->SetIsMarkedForDeletion(true);
						bullet->SetIsMarkedForDeletion(true);
						gameState.m_score += enemy->GetScoreValue();
						Debug_PrintLine("New Score: %d", gameState.m_score);
					}
				}

				// Check if bullet is out of play area
				if (!bullet->GetIsMarkedForDeletion())
				{
					if(currentPosition.m_y <= 1 || dY >= currentPosition.m_y || currentPosition.m_y - dY <= 0)
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
			for (uint8_t i = 0; i < gameState.m_numEnemies; i++)
			{
				Enemy* enemy = gameState.m_enemies[i];
				uint8_t mul = (b ? 1 : -1);
				XYCoord curPos = enemy->GetPosition();
				curPos.m_x = curPos.m_x + (mul * 5);
				enemy->SetPosition(curPos);
			}
			b = !b;


		// Delete to-be-deleted entities
		
			// Bullets
			for(uint8_t i = 0; i < gameState.m_numBullets; i++)
			{
				Bullet* bullet = gameState.m_bullets[i];
				if(bullet->GetIsMarkedForDeletion())
				{
					gameState.DeleteBullet(i);
					i -= 1;
				}
			}

			// Enemies
			for(uint8_t i = 0; i < gameState.m_numEnemies; i++)
			{
				Enemy* enemy = gameState.m_enemies[i];
				if(enemy->GetIsMarkedForDeletion())
				{
					gameState.DeleteEnemy(i);
					i -= 1;
				}
			}

	} break;
	default: break;
	}

	return state;
}
