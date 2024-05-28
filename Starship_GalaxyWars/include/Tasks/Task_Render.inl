#include "Tasks/Tasks.h"
#include "ScreenRegion.h"
#include "GameState.h"
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
