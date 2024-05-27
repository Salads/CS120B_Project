#pragma once

#include "Tasks.h"
#include "JoystickDirection.h"
#include "ScreenRegion.h"
#include "GameState.h"
#include "Enemy.h"
#include "Bullet.h"

int Tick_Render(int state)
{
	switch(state) // transitions
	{
		case TS_RENDER_INIT: state = TS_RENDER_DORENDER; break;
		case TS_RENDER_DORENDER: break;
		default: break;
	}

	switch(state) // state actions
	{
		case TS_RENDER_INIT: break;
		case TS_RENDER_DORENDER:
		{
			GameState& gameState = GameState::Get();
			ST7735SClient& renderer = ST7735SClient::Get();
			for(int i = 0; i < gameState.m_numEnemies; i++)
			{
				Enemy* enemy = gameState.m_enemies[i];
				if(enemy->GetRenderDirty())
				{
					renderer.RenderEntity(enemy);
					enemy->SetRenderDirty(false);
				}
			}

			if(gameState.m_player->GetRenderDirty())
			{
				renderer.RenderEntity(gameState.m_player);
				gameState.m_player->SetRenderDirty(false);
			}

			for(int i = 0; i < gameState.m_numBullets; i++)
			{
				Bullet* bullet = gameState.m_bullets[i];
				if(bullet->GetRenderDirty())
				{
					renderer.RenderEntity(bullet, false);
					bullet->SetRenderDirty(false);
				}
			}

		} break;
		default: break;
	}

	return state;
}

int Tick_Buttons(int state)
{
	switch(state)
	{
		case TS_BUTTONS_INIT: state = TS_BUTTONS_SAMPLE; break;
		case TS_BUTTONS_SAMPLE: break;
		default: break;
	}

	switch (state)
	{
	case TS_BUTTONS_INIT: break;
	case TS_BUTTONS_SAMPLE:
	{
		// [0-7] PORTD (8bit)
		// [8-13] PORTB (6bit)
		// [A0-A5] PORTC (6bit)
		// Output: DDR=1, PORT=0
		// PINx: Read Input
		// PORTx: Set Output

		bool isButtonDown = GetBit(PIND, PIND7);
		GameState::Get().m_fireButton = isButtonDown;

	} break;
	default: break;
	}

	return state;
}

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
			static bool b2 = false;
			for(uint8_t bIdx = 0; bIdx < gameState.m_numBullets; bIdx++)
			{
				Bullet* bullet = gameState.m_bullets[bIdx];
				float dY = (float)K_BULLET_SPEED * gameState.m_deltaTimeMS;
				XYCoord currentPosition = bullet->GetPosition();
				if(currentPosition.m_y - dY <= 2)
				{
					bullet->SetIsMarkedForDeletion(true);
					Serial_PrintLine("Mark Delete Bullet");
				}
				else
				{
					bullet->SetPosition(currentPosition.m_x, currentPosition.m_y - dY);
				}
			}
			b2 = !b2;


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

	} break;
	default: break;
	}

	return state;
}

int Tick_Joystick(int state)
{
	switch(state)
	{
		case TS_JOYSTICK_INIT: state = TS_JOYSTICK_SAMPLE; break;
		case TS_JOYSTICK_SAMPLE: break;
		default: break;
	}

	switch (state)
	{
	case TS_JOYSTICK_INIT: break;
	case TS_JOYSTICK_SAMPLE:
	{
		
	} break;
	default: break;
	}

	return state;
}

int Tick_Timing(int state)
{
	switch(state)
	{
		case TS_TIMING_INIT: state = TS_TIMING_UPDATE; break;
		case TS_TIMING_UPDATE: break;
		default: break;
	}

	switch (state)
	{
	case TS_TIMING_INIT: break;
	case TS_TIMING_UPDATE:
	{
		GameState::Get().UpdateDeltaTime();
	} break;
	default: break;
	}

	return state;
}
