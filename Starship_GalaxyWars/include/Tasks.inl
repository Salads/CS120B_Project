#pragma once

#include "Tasks.h"
#include "JoystickDirection.h"
#include "ScreenRegion.h"
#include "GameState.h"
#include "Enemy.h"

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
					// Render over previous position with background color.
					ScreenRegion lastRegion = enemy->GetLastRenderRegion();
					renderer.SetRegion(lastRegion);
					renderer.FillCurrentScreenRegion(255, 255, 255);

					// Render new position
					ScreenRegion newRegion = enemy->GetRenderRegion();
					renderer.SetRegion(newRegion);
					renderer.FillCurrentScreenRegion(120, 120, 0);
					
					enemy->SetRenderDirty(false);
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
