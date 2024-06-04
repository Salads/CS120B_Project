#include "DebugLevel_ScreenSize.h"
#include "GameState.h"
#include "ST7735SClient.h"
#include <stdlib.h>

#if DEBUG_SCREENSIZE
DebugLevel_ScreenSize::DebugLevel_ScreenSize()
{
	m_text = new TextRenderObject();
	m_text->SetPosition(30, 65);
}

void DebugLevel_ScreenSize::Update()
{
	GameState& gameState = GameState::Get();
	static JoystickDirection lastJoyX = JD_CENTER;
	static JoystickDirection lastJoyY = JD_CENTER;

	JoystickDirection curJoyX = gameState.m_joystickDirectionX;
	JoystickDirection curJoyY = gameState.m_joystickDirectionY;

	if(curJoyX != JD_CENTER && curJoyX != lastJoyX)
	{
		if(curJoyX == JD_RIGHT)
		{
			if(m_debugWidth < SCREEN_WIDTH)
			{
				m_debugWidth++;
			}
		}
		else
		{
			if(m_debugWidth > 1)
			{
				m_debugWidth--;
			}
		}
	}
	else if(curJoyY != JD_CENTER && curJoyY != lastJoyY)
	{
		if(curJoyY == JD_DOWN)
		{
			if(m_debugHeight < SCREEN_WIDTH)
			{
				m_debugHeight++;
			}
		}
		else
		{
			if(m_debugHeight > 1)
			{
				m_debugHeight--;
			}
		}
	}

	if(m_debugWidthLast != m_debugWidth || m_debugHeightLast != m_debugHeight)
	{
		char buffer[64];
		sprintf(buffer, "Size: %dx%d", m_debugWidth, m_debugHeight);
		m_text->SetText(buffer);
	}

	m_debugWidthLast = m_debugWidth;
	m_debugHeightLast = m_debugHeight;
}

void DebugLevel_ScreenSize::Render()
{
	// Draw the background size
	if(m_text->GetRenderDirty())
	{
		ST7735SClient& renderer = ST7735SClient::Get();
		ScreenRegion background;

		renderer.SetRegion(background);
		renderer.FillCurrentScreenRegion(0, 0, 0);

		background.m_startX = 1;
		background.m_startY = 1;
		background.m_endX = m_debugWidth;
		background.m_endY = m_debugHeight;
		renderer.SetRegion(background);
		renderer.FillCurrentScreenRegion(255, 255, 255);
	}

	m_text->Render();
}

DoneReason DebugLevel_ScreenSize::GetDoneReason()
{
	return DoneReason_None;
}
#endif