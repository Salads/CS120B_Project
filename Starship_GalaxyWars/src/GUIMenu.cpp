#include "GUIMenu.h"
#include "GameState.h"
#include <avr/pgmspace.h>
#include "SerialMonitor.h"
#include "ST7735SClient.h"

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
	m_width = 0;
	m_height = 0;
	
	m_largestOptionWidth = 0;

	for(uint8_t i = 0; i < m_numOptions; i++)
	{
		const char* optionText = config.m_optionTexts[i];
		m_textObjects[i] = new TextRenderObject();
		m_textObjects[i]->SetText(optionText);
		
		m_largestOptionWidth = max(m_largestOptionWidth, m_textObjects[i]->GetWidth());
	}

	m_cursorTexture = kCursorTexture;
	m_cursor = new SimpleRenderObject(m_cursorTexture);

	UpdateLayout();

	// Set all objects positions to themselves, since we want to 
	// make sure last position isn't different upon first initialization.
	// Ideally we would want a flag or something that prevents setting it...
	for(uint8_t i = 0; i < m_numOptions; i++)
	{
		m_textObjects[i]->SetPosition(m_textObjects[i]->GetPosition());
	}

	m_cursor->SetPosition(m_cursor->GetPosition());

	SetRenderDirty(true);
}

uint8_t GUIMenu::GetCursorLessSpace()
{
	return m_largestOptionWidth;
}

void GUIMenu::UpdateLayout()
{
	// Right now we don't have "local" coordinates, and true "parenting" of objects.
	// Everything is just a dumb container. So, we need to manually get all the positions ourselves
	// and calculate the true position that way.
	XYCoord currentMenuPos = GetPosition();

	// Options are left-justified
	uint8_t cursorWidth = m_cursor->GetWidth();
	uint8_t cursorGap = 5;
	uint8_t xCursorPos = currentMenuPos.m_x;

	uint8_t yPos = currentMenuPos.m_y;
	uint8_t xPos = xCursorPos + cursorWidth + cursorGap;
	m_optionXPosition = xPos;

	m_width  = xPos + m_largestOptionWidth - currentMenuPos.m_x;
	m_height = yPos - currentMenuPos.m_y;

	for(uint8_t i = 0; i < m_numOptions; i++)
	{
		m_optionYPositions[i] = yPos;
		m_textObjects[i]->SetPosition(m_optionXPosition, m_optionYPositions[i]);
		yPos += m_textObjects[i]->GetHeight();
		
		m_height += m_textObjects[i]->GetHeight();
	}

	m_cursor->SetPosition(xCursorPos, m_optionYPositions[m_selectedIdx]);

	SetRenderDirty(true);
}

void GUIMenu::OnSetPosition()
{
	UpdateLayout();
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
		if(object->GetRenderDirty() || GetRenderDirty())
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