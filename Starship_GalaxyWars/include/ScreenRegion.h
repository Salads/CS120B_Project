#pragma once

#include "Types.h"
#include "Defines.h"

struct ScreenRegion
{
	ScreenRegion()
		: m_startX(1), m_endX(SCREEN_WIDTH - 1), m_startY(1), m_endY(SCREEN_HEIGHT - 1){};
	ScreenRegion(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1)
		: m_startX(x0), m_endX(x1), m_startY(y0), m_endY(y1) {};

	uint8_t m_startX;
	uint8_t m_endX;

	uint8_t m_startY;
	uint8_t m_endY;
};
