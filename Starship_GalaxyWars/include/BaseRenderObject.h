#pragma once

#include <stdint.h>
#include "XYCoord.h"
#include "ScreenRegion.h"

class BaseRenderObject
{
public:
    uint16_t* GetTextureData();
	uint16_t GetTextureDataSize();

	virtual void Render() = 0;
	void SetPosition(int16_t x, int16_t y);
	void SetPosition(XYCoord newPosition);
	void SetLastRenderedPosition(ScreenRegion region);
	void SetRenderDirty(bool dirty);
	bool GetRenderDirty() {return m_renderDirty;}
	void ClearFromDisplay();
	ScreenRegion GetLastRenderRegion();
	ScreenRegion GetRenderRegion();

	uint8_t GetWidth();
	uint8_t GetHeight();

	XYCoord GetPosition();

protected:
    virtual void UpdateSize() = 0;
protected:
    bool m_renderDirty = false;

	uint8_t m_width = 25;
	uint8_t m_height = 25;

	XYCoord m_position;
	XYCoord m_lastRenderedPosition;

	// There's no data integrity checking between texture data and
	// entity size. There's also no texture stretching.
	// Will probably crash if you mismatch texture data size with entity size.
	uint16_t* m_textureData;
	uint16_t  m_textureDataSize;

};
