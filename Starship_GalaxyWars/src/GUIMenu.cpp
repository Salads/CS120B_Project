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
	(uint8_t*)texture_cursor,
	5*9,
	5,9,
	TextureFormat_16Bit
};

void GUIMenu::AddOption(const char* newOptionText)
{
	const char* optionText = newOptionText;
	m_textObjects[m_numOptions] = new TextRenderObject();
	m_textObjects[m_numOptions]->SetText(optionText);
	
	m_largestOptionWidth = max(m_largestOptionWidth, m_textObjects[m_numOptions]->GetWidth());
	m_numOptions++;

	UpdateLayout();
	SetRenderDirty(true);
}

GUIMenu::GUIMenu()
{
	m_width = 0;
	m_height = 0;
	m_numOptions = 0;
	
	m_largestOptionWidth = 0;

	m_cursorTexture = kCursorTexture;
	m_cursor = new SimpleRenderObject(m_cursorTexture);
}

GUIMenu::~GUIMenu()
{
	for (uint8_t i = 0; i < m_numOptions; i++)
	{
		if(m_textObjects[i])
		{
			delete m_textObjects[i];
		}
	}

	if(m_cursor)
	{
		delete m_cursor;
	}
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
	uint8_t cursorWidth = 0;
	uint8_t cursorGap = 0;
	cursorWidth = m_cursor->GetWidth();
	cursorGap = 5;
	
	uint8_t xCursorPos = currentMenuPos.m_x + m_borderThickness + m_borderGap;

	uint8_t yPos = currentMenuPos.m_y + m_borderThickness + m_borderGap;
	uint8_t xPos = xCursorPos + cursorWidth + cursorGap;

	m_optionXPosition = xPos;

	m_width  = m_borderThickness + m_borderGap + cursorWidth + cursorGap + m_largestOptionWidth + m_borderGap + m_borderThickness;
	m_height = m_borderThickness + m_borderGap; // height without contents, content heights added later

	for(uint8_t i = 0; i < m_numOptions; i++)
	{
		m_optionYPositions[i] = yPos;
		m_textObjects[i]->SetPosition(m_optionXPosition, m_optionYPositions[i]);
		m_textObjects[i]->SetInitialized();

		uint8_t objHeight = m_textObjects[i]->GetHeight();
		yPos += objHeight;
		m_height += objHeight;
	}

	m_height += m_borderThickness + m_borderGap; // The bottom extra space

	m_cursor->SetPosition(xCursorPos, m_optionYPositions[m_selectedIdx]);
	m_cursor->SetInitialized();

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
}

void GUIMenu::SelectNextOption()
{
	if(m_selectedIdx >= m_numOptions - 1) return;
	m_selectedIdx++;
	m_cursor->SetPosition(m_optionXPosition - m_cursor->GetWidth() - 5, m_optionYPositions[m_selectedIdx]);
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

		if(gameState.m_fireButton && !gameState.m_fireButtonHeld) // only "fresh" on downs
		{
			m_acceptedSelection = true;
		}
	}

	lastDirection = gameState.m_joystickDirectionY;
}

void GUIMenu::Unlock()
{
	m_acceptedSelection = false;
}

void GUIMenu::OnSetRenderDirty(bool newDirty)
{
	// Because of the border rendering, theres a situation where
	// the background is dirty, but the objects haven't changed, so
	// technically they are not. 
	// This causes the background to render, but child objects to be 
	// not rendered. (blank)
	// We set all child objects dirty here.

	for(uint8_t i = 0; i < m_numOptions; i++)
	{
		m_textObjects[i]->SetRenderDirty(true);
	}

	m_cursor->SetRenderDirty(true);
}

void GUIMenu::Render(bool clearLastPosition)
{
	if(GetRenderDirty())
	{
		// Render the "border", which is just 
		// a white background, then a smaller fill box
		// to "hollow out" the white background
		// Could optimize this, but UI isn't updated that much so probably not worth

		ST7735SClient& renderer = ST7735SClient::Get();

		// First clear last position
		ScreenRegion lastRegion = GetLastRenderRegion();
		renderer.SetRegion(lastRegion);
		renderer.FillCurrentScreenRegionPacked16(renderer.m_backgroundColor);

		// Fill new region with white (the border)
		// This is our current size, including the border
		ScreenRegion borderRegion = GetRenderRegion();
		renderer.SetRegion(borderRegion);
		renderer.FillCurrentScreenRegionRGB24(255, 255, 255);

		// Now we hollow it out
		ScreenRegion hollowRegion = borderRegion;
		hollowRegion.m_startX += m_borderThickness;
		hollowRegion.m_startY += m_borderThickness;
		hollowRegion.m_endX   -= m_borderThickness;
		hollowRegion.m_endY   -= m_borderThickness;
		renderer.SetRegion(hollowRegion);
		renderer.FillCurrentScreenRegionPacked16(renderer.m_backgroundColor);

		SetRenderDirty(false);
	}

	// Now we render the rest of our child objects on top of this.
	for(uint8_t i = 0; i < m_numOptions; i++)
	{
		TextRenderObject* object = m_textObjects[i];
		object->Render();
	}

	m_cursor->Render();
}