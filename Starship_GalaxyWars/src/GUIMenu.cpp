#include "GUIMenu.h"
#include "GameState.h"
#include <avr/pgmspace.h>
#include "SerialMonitor.h"

// 'menu_cursor, 5x9px
const uint16_t texture_cursor [] PROGMEM = 
{
	0x2589, 0x0000, 0x0000, 0x0000, 0x0000, 0x2589, 0x2589, 0x0000, 0x0000, 0x0000, 0x2589, 0x2589, 0x2589, 0x0000, 0x0000, 0x2589, 
	0x2589, 0x2589, 0x2589, 0x0000, 0x2589, 0x2589, 0x2589, 0x2589, 0x2589, 0x2589, 0x2589, 0x2589, 0x2589, 0x0000, 0x2589, 0x2589, 
	0x2589, 0x0000, 0x0000, 0x2589, 0x2589, 0x0000, 0x0000, 0x0000, 0x2589, 0x0000, 0x0000, 0x0000, 0x0000
};

const Texture kCursorTexture = 
{
	texture_cursor,
	5*9,
	5,10
};

GUIMenu::GUIMenu(const GUIMenuConfig& config)
{
	m_numOptions = config.m_numOptions;
	m_width = config.m_frameWidth;
	m_height = config.m_frameHeight;
	
	uint8_t largestWidth = 0;

	for(uint8_t i = 0; i < m_numOptions; i++)
	{
		const char* optionText = config.m_optionTexts[i];
		m_textObjects[i] = new TextRenderObject();
		m_textObjects[i]->SetText(optionText);
		largestWidth = max(largestWidth, m_textObjects[i]->GetWidth());
	}

	// Centered, but left-justified.
	uint8_t yMargin = 10;
	m_optionXPosition = 15 + (m_width/2) - (largestWidth/2);
	for(uint8_t i = 0; i < m_numOptions; i++)
	{
		m_optionYPositions[i] = yMargin + (i * 15);
		m_textObjects[i]->SetPosition(m_optionXPosition, m_optionYPositions[i]);
	}

	m_cursorTexture = kCursorTexture;
	m_cursor = new SimpleRenderObject(m_cursorTexture);
	m_cursor->SetPosition(m_optionXPosition - m_cursor->GetWidth() - 5, m_optionYPositions[0]);
	SetRenderDirty(true);
}

bool GUIMenu::GetAcceptedSelection()
{
	return m_acceptedSelection;
}

void GUIMenu::SelectPreviousOption()
{
	if(m_selectedIdx <= 0) return;
	m_selectedIdx--;
	m_cursor->SetPosition(m_optionXPosition - m_cursor->GetWidth() - 5, m_optionYPositions[m_selectedIdx]);
	SetRenderDirty(true);
}

void GUIMenu::SelectNextOption()
{
	if(m_selectedIdx >= m_numOptions - 1) return;
	m_selectedIdx++;
	m_cursor->SetPosition(m_optionXPosition - m_cursor->GetWidth() - 5, m_optionYPositions[m_selectedIdx]);
	SetRenderDirty(true);
}

uint8_t GUIMenu::GetSelectedOptionIdx()
{
	return m_selectedIdx;
}

void GUIMenu::Update()
{
	static JoystickDirection lastDirection = JD_CENTER; // bad
	GameState& gameState = GameState::Get();


	if(!m_acceptedSelection)
	{
		if(lastDirection == JD_CENTER && gameState.m_joystickDirectionY == JD_DOWN)
		{
			SelectNextOption();
		}
		else if(lastDirection == JD_CENTER && gameState.m_joystickDirectionY == JD_UP)
		{
			SelectPreviousOption();
		}

		if(gameState.m_fireButton)
		{
			m_acceptedSelection = true;
		}
	}

	lastDirection = gameState.m_joystickDirectionY;
}

void GUIMenu::Render(bool clearLastPosition)
{
	for(uint8_t i = 0; i < m_numOptions; i++)
	{
		TextRenderObject* object = m_textObjects[i];
		if(object->GetRenderDirty())
		{
			object->Render();
			object->SetRenderDirty(false);
		}
	}

	if(m_cursor->GetRenderDirty())
	{
		m_cursor->Render();
		m_cursor->SetRenderDirty(false);
	}
}