#pragma once

#include "Types.h"
#include "Defines.h"

struct ScreenRegion
{
	ScreenRegion()
		: m_startX(0), m_endX(SCREEN_WIDTH), m_startY(0), m_endY(SCREEN_HEIGHT){};
	ScreenRegion(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1)
		: m_startX(x0), m_endX(x1), m_startY(y0), m_endY(y1) {};

	uint8_t m_startX;
	uint8_t m_endX;

	uint8_t m_startY;
	uint8_t m_endY;
};
