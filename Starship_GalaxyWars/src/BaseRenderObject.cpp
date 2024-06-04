#include "BaseRenderObject.h"
#include "ST7735SClient.h"
#include "Texture.h"

BaseRenderObject::BaseRenderObject(BaseRenderObject* parent)
{
	m_parent = parent;
}

BaseRenderObject::~BaseRenderObject()
{}

void BaseRenderObject::SetInitialized()
{
	m_initialized = true;
}

bool BaseRenderObject::GetInitialized()
{
	return m_initialized;
}

void BaseRenderObject::ClearFromDisplay()
{
	// Have the renderer clear our current region with background color
	ST7735SClient& renderer = ST7735SClient::Get();
	ScreenRegion currentRegion = GetRenderRegion();
	renderer.SetRegion(currentRegion);
	renderer.FillCurrentScreenRegionPacked16(renderer.m_backgroundColor);
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
	x = clamp(x, 1, SCREEN_WIDTH - m_width - 1);
	y = clamp(y, 1, SCREEN_HEIGHT - m_height - 1);

	if(GetInitialized())
	{
		m_lastRenderedPosition = m_position;
		m_position = XYCoord(x, y);
	}
	else
	{
		XYCoord newPosition = XYCoord(x, y);
		m_lastRenderedPosition = newPosition;
		m_position = newPosition;
	}
	
	SetRenderDirty(true);

	OnSetPosition();
}

void BaseRenderObject::OnSetPosition()
{
	// Nothing here.
	// Usefull for text rendering objects, with child objects to render.
}

void BaseRenderObject::OnSetRenderDirty(bool newDirty)
{
	// Nothing here.
	// Used for objects that have child render objects, so they can set their dirty flags there.
}

void BaseRenderObject::SetPosition(XYCoord newPosition)
{
	newPosition.m_x = clamp(newPosition.m_x, 1, SCREEN_WIDTH - m_width - 1);
	newPosition.m_y = clamp(newPosition.m_y, 1, SCREEN_HEIGHT - m_height - 1);

	if(GetInitialized())
	{
		m_lastRenderedPosition = m_position;
		m_position = newPosition;
	}
	else
	{
		m_lastRenderedPosition = newPosition;
		m_position = newPosition;
	}
	
	SetRenderDirty(true);

	OnSetPosition();
}

void BaseRenderObject::SetRenderDirty(bool dirty)
{
	m_renderDirty = dirty;
	OnSetRenderDirty(dirty);
}

// Screen region on the ST7735S is from range [1,SCREEN_DIM)
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
