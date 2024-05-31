#pragma once

#include <stdint.h>
#include "XYCoord.h"
#include "ScreenRegion.h"

class BaseRenderObject
{
public:
	virtual void Render(bool clearLastPosition = true) = 0;
	void SetPosition(int16_t x, int16_t y);
	void SetPosition(XYCoord newPosition);
	void SetRenderDirty(bool dirty);
	bool GetRenderDirty() {return m_renderDirty;}
	void ClearFromDisplay();
	ScreenRegion GetLastRenderRegion();
	ScreenRegion GetRenderRegion();

	uint8_t GetWidth();
	uint8_t GetHeight();

	XYCoord GetPosition();

protected:
	virtual void OnSetPosition();

protected:
    bool m_renderDirty = false;

	uint8_t m_width = 25;
	uint8_t m_height = 25;

	XYCoord m_position;
	XYCoord m_lastRenderedPosition;

};
