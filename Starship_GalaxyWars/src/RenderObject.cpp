#include "RenderObject.h"
#include "ST7735SClient.h"

void RenderObject::ClearFromDisplay()
{
	// Have the renderer clear our current region with background color
	ST7735SClient& renderer = ST7735SClient::Get();
	ScreenRegion currentRegion = GetRenderRegion();
	renderer.SetRegion(currentRegion);
	renderer.FillCurrentScreenRegion(renderer.m_backgroundColor);
}

XYCoord RenderObject::GetPosition()
{
	return m_position;
}

void RenderObject::SetLastRenderedPosition(ScreenRegion region)
{
	m_lastRenderedPosition = XYCoord(region.m_startX, region.m_startY);
}

uint16_t RenderObject::GetTextureDataSize()
{
	return m_textureDataSize;
}

uint16_t* RenderObject::GetTextureData()
{
	return m_textureData;
}

uint8_t RenderObject::GetWidth()
{
	return m_width;
}

uint8_t RenderObject::GetHeight()
{
	return m_height;
}

void RenderObject::SetPosition(int16_t x, int16_t y)
{
	x = clamp(x, 0, SCREEN_WIDTH - m_width - 1);
	y = clamp(y, 0, SCREEN_HEIGHT - m_height - 1);

	m_lastRenderedPosition = m_position;
	m_position = XYCoord(x, y);
	m_renderDirty = true;
}

void RenderObject::SetPosition(XYCoord newPosition)
{
	newPosition.m_x = clamp(newPosition.m_x, 1, SCREEN_WIDTH - m_width - 1);
	newPosition.m_y = clamp(newPosition.m_y, TOP_HUD_HEIGHT, SCREEN_HEIGHT - BOTTOM_HUD_HEIGHT - m_height);

	m_lastRenderedPosition = m_position;
	m_position = newPosition;
	m_renderDirty = true;
}

void RenderObject::SetRenderDirty(bool dirty)
{
	m_renderDirty = dirty;
}

ScreenRegion RenderObject::GetLastRenderRegion()
{
	ScreenRegion result(
		m_lastRenderedPosition.m_x + 1,
		m_lastRenderedPosition.m_x + m_width,
		m_lastRenderedPosition.m_y + 1,
		m_lastRenderedPosition.m_y + m_height + 2
	);

	return result;
}

ScreenRegion RenderObject::GetRenderRegion()
{
	ScreenRegion result(
		m_position.m_x + 1,
		m_position.m_x + m_width,
		m_position.m_y + 1,
		m_position.m_y + m_height + 2
	);

	return result;
}
