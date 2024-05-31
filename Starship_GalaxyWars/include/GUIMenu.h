#pragma once

#include <stdint.h>
#include "BaseRenderObject.h"

struct GUIMenu : public BaseRenderObject
{
	GUIMenu();
	void SelectPreviousOption();
	void SelectNextOption();
	void Render();

public:
	uint8_t m_selectedIdx = 0;

protected:
	uint16_t* m_backgroundTexture;
	uint16_t* m_cursorTexture;
	
	uint8_t   m_optionXPosition = 0;
	uint8_t   m_optionYPositions[5];
	uint8_t   m_numOptions = 0;
};
