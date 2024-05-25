#pragma once

#include "Types.h"
#include "XYCoord.h"
#include "ScreenRegion.h"

class Entity
{
public:
	Entity();
	bool GetCollides(Entity &other);
	//virtual uint8_t* GetTextureData() = 0;

	void SetPosition(uint8_t x, uint8_t y);
	void SetRenderDirty(bool dirty);
	bool GetRenderDirty() {return m_renderDirty;}
	ScreenRegion GetLastRenderRegion();
	ScreenRegion GetRenderRegion();
	
protected:

	bool m_renderDirty = false;

	uint8_t m_width = 25;
	uint8_t m_height = 25;

	XYCoord m_position;
	XYCoord m_lastPosition;
};
