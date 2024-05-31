#pragma once

#include <stdint.h>
#include "BaseRenderObject.h"
#include "Texture.h"

struct GUIMenu : public BaseRenderObject
{
	GUIMenu();
	void SelectPreviousOption();
	void SelectNextOption();
	void Render();

public:
	uint8_t m_selectedIdx = 0;

protected:
	Texture   m_backgroundTexture;
	Texture   m_cursorTexture;
	
	uint8_t   m_optionXPosition = 0;
	uint8_t   m_optionYPositions[5];
	uint8_t   m_numOptions = 0;
};
