#pragma once

#include <stdint.h>

struct GUIMenu
{
	GUIMenu();

public:
	uint8_t m_selectedIdx = 0;

protected:
	uint16_t* m_backgroundTexture;
	uint16_t* m_cursorTexture;
	
	uint8_t   m_optionStartX = 0;
	uint8_t   m_optionYPositions[5];
};
