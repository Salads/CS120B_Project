#include "Tasks/Tasks.h"
#include "GameState.h"
#include "Bullet.h"

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
			Debug_PrintLine("Pew Pew!");
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
			// Debug_PrintLine("SinceLastFire: %d, FireDown: %d, NumBullets: %d", 
			// 	gameState.m_timeSinceLastFireMS, 
			// 	gameState.m_numBullets,
			// 	gameState.m_fireButton);
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

			// Enemies
			static bool b = true;
			for (uint8_t i = 0; i < gameState.m_numEnemies; i++)
			{
				Enemy* enemy = gameState.m_enemies[i];
				uint8_t mul = (b ? 1 : -1);
				XYCoord curPos = enemy->GetPosition();
				curPos.m_y = curPos.m_y + (mul * 25);
				enemy->SetPosition(curPos);
			}
			b = !b;

			// Bullets
			for(uint8_t bIdx = 0; bIdx < gameState.m_numBullets; bIdx++)
			{
				Bullet* bullet = gameState.m_bullets[bIdx];
				float dY = (float)K_BULLET_SPEED * gameState.m_deltaTimeMS;
				XYCoord currentPosition = bullet->GetPosition();

				if(currentPosition.m_y <= 1 || dY >= currentPosition.m_y || currentPosition.m_y - dY <= 0)
				{
					bullet->SetIsMarkedForDeletion(true);
					Serial_PrintLine("Mark Delete Bullet");
				}
				else
				{
					bullet->SetPosition(currentPosition.m_x, currentPosition.m_y - dY);
				}
			}


		// Delete to-be-deleted entities
		
			// Bullets
			for(uint8_t i = 0; i < gameState.m_numBullets; i++)
			{
				Bullet* bullet = gameState.m_bullets[i];
				if(bullet->GetIsMarkedForDeletion())
				{
					bullet->ClearFromDisplay();
					gameState.DeleteBullet(i);
					i -= 1;
				}
			}

	} break;
	default: break;
	}

	return state;
}
