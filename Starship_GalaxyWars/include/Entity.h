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

	uint8_t GetWidth();
	uint8_t GetHeight();
	
protected:

	bool m_renderDirty = false;

	uint8_t m_width = 25;
	uint8_t m_height = 25;

	XYCoord m_position;
	XYCoord m_lastPosition;

	// There's no data integrity checking between texture data and
	// entity size. There's also no texture stretching.
	// Will probably crash if you mismatch texture data size with entity size.
	uint8_t* m_textureData;
};
