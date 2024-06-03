#include "BaseRenderObject.h"
#include "ST7735SClient.h"
#include "Texture.h"

BaseRenderObject::BaseRenderObject(BaseRenderObject* parent)
{
	m_parent = parent;
}

BaseRenderObject::~BaseRenderObject()
{}

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
	
	SetRenderDirty(true);

	OnSetPosition();
}

void BaseRenderObject::OnSetPosition()
{
	// Nothing here.
	// Usefull for text rendering objects, with child objects to render.
}

void BaseRenderObject::SetPosition(XYCoord newPosition)
{
	newPosition.m_x = clamp(newPosition.m_x, 0, SCREEN_WIDTH - m_width - 1);
	newPosition.m_y = clamp(newPosition.m_y, 0, SCREEN_HEIGHT - m_height - 1);

	m_lastRenderedPosition = m_position;
	m_position = newPosition;
	
	SetRenderDirty(true);

	OnSetPosition();
}

void BaseRenderObject::SetRenderDirty(bool dirty)
{
	m_renderDirty = dirty;

	if(m_renderDirty && m_parent != nullptr)
	{
		m_parent->SetRenderDirty(m_renderDirty);
	}
}

ScreenRegion BaseRenderObject::GetLastRenderRegion()
{
	ScreenRegion result(
		m_lastRenderedPosition.m_x,
		m_lastRenderedPosition.m_x + m_width - 1,
		m_lastRenderedPosition.m_y,
		m_lastRenderedPosition.m_y + m_height - 1
	);

	return result;
}

ScreenRegion BaseRenderObject::GetRenderRegion()
{
	ScreenRegion result(
		m_position.m_x,
		m_position.m_x + m_width - 1,
		m_position.m_y,
		m_position.m_y + m_height - 1
	);

	return result;
}
