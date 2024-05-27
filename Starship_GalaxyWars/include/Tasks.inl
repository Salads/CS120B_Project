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
	case TS_UPDATE_DOUPDATE: break;
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
		GameState& gameState = GameState::Get();
		gameState.m_lastFrameMS = gameState.m_timeMS;
	} break;
	default: break;
	}

	return state;
}
