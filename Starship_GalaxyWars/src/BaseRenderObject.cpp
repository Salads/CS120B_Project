#include "BaseRenderObject.h"
#include "ST7735SClient.h"

void BaseRenderObject::ClearFromDisplay()
{
	// Have the renderer clear our current region with background color
	ST7735SClient& renderer = ST7735SClient::Get();
	ScreenRegion currentRegion = GetRenderRegion();
	renderer.SetRegion(currentRegion);
	renderer.FillCurrentScreenRegion(renderer.m_backgroundColor);
}

XYCoord BaseRenderObject::GetPosition()
{
	return m_position;
}

void BaseRenderObject::SetLastRenderedPosition(ScreenRegion region)
{
	m_lastRenderedPosition = XYCoord(region.m_startX, region.m_startY);
}

uint16_t BaseRenderObject::GetTextureDataSize()
{
	return m_textureDataSize;
}

uint16_t* BaseRenderObject::GetTextureData()
{
	return m_textureData;
}

uint8_t BaseRenderObject::GetWidth()
{
	return m_width;
}

uint8_t BaseRenderObject::GetHeight()
{
	return m_height;
}

void BaseRenderObject::SetPosition(int16_t x, int16_t y)
{
	x = clamp(x, 0, SCREEN_WIDTH - m_width - 1);
	y = clamp(y, 0, SCREEN_HEIGHT - m_height - 1);

	m_lastRenderedPosition = m_position;
	m_position = XYCoord(x, y);
	m_renderDirty = true;
}

void BaseRenderObject::SetPosition(XYCoord newPosition)
{
	newPosition.m_x = clamp(newPosition.m_x, 1, SCREEN_WIDTH - m_width - 1);
	newPosition.m_y = clamp(newPosition.m_y, TOP_HUD_HEIGHT, SCREEN_HEIGHT - BOTTOM_HUD_HEIGHT - m_height);

	m_lastRenderedPosition = m_position;
	m_position = newPosition;
	m_renderDirty = true;
}

void BaseRenderObject::SetRenderDirty(bool dirty)
{
	m_renderDirty = dirty;
}

ScreenRegion BaseRenderObject::GetLastRenderRegion()
{
	ScreenRegion result(
		m_lastRenderedPosition.m_x + 1,
		m_lastRenderedPosition.m_x + m_width,
		m_lastRenderedPosition.m_y + 1,
		m_lastRenderedPosition.m_y + m_height + 2
	);

	return result;
}

ScreenRegion BaseRenderObject::GetRenderRegion()
{
	ScreenRegion result(
		m_position.m_x + 1,
		m_position.m_x + m_width,
		m_position.m_y + 1,
		m_position.m_y + m_height + 2
	);

	return result;
}
