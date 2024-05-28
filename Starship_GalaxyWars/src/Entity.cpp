
#include "Entity.h"
#include "ScreenRegion.h"
#include "ST7735SClient.h"

Entity::Entity()
{
	m_lastRenderedPosition = XYCoord(0, 0);
	m_position = XYCoord(0,0);
}

Entity::~Entity()
{
	
}

void Entity::ClearFromDisplay()
{
	// Have the renderer clear our current region with background color
	ST7735SClient& renderer = ST7735SClient::Get();
	ScreenRegion currentRegion = GetRenderRegion();
	renderer.SetRegion(currentRegion);
	renderer.FillCurrentScreenRegion(renderer.m_backgroundColor);
}

bool Entity::GetIsMarkedForDeletion()
{
	return m_markedForDelete;
}

void Entity::SetIsMarkedForDeletion(bool shouldDelete)
{
	m_markedForDelete = shouldDelete;
	if(m_markedForDelete)
	{
		ClearFromDisplay();
	}
}

XYCoord Entity::GetPosition()
{
	return m_position;
}

void Entity::SetLastRenderedPosition(ScreenRegion region)
{
	m_lastRenderedPosition = XYCoord(region.m_startX, region.m_startY);
}

uint16_t Entity::GetTextureDataSize()
{
	return m_textureDataSize;
}

uint16_t* Entity::GetTextureData()
{
	return m_textureData;
}

uint8_t Entity::GetWidth()
{
	return m_width;
}

uint8_t Entity::GetHeight()
{
	return m_height;
}

bool Entity::GetCollides(Entity &other)
{
	// simple "box" collision checking
	// it's just an arcade game
	uint8_t this_x1 = m_position.m_x; 			 // left edge
	uint8_t this_x2 = m_position.m_x + m_width;  // right edge
	uint8_t this_y1 = m_position.m_y;            // top edge
	uint8_t this_y2 = m_position.m_y + m_height; // bottom edge

	uint8_t other_x1 = other.m_position.m_x;                  	// left edge
	uint8_t other_x2 = other.m_position.m_x + other.m_width;	// right edge
	uint8_t other_y1 = other.m_position.m_y;					// top edge
	uint8_t other_y2 = other.m_position.m_y + other.m_height;	// bottom edge

	return (this_x1 <= other_x2 && this_x2 >= other_x1) &&
		   (this_y1 <= other_y2 && this_y2 >= other_y1);
}

void Entity::SetPosition(int16_t x, int16_t y)
{
	x = clamp(x, 1, SCREEN_WIDTH - m_width - 2);
	y = clamp(y, 1, SCREEN_HEIGHT - m_height - 2);

	m_lastRenderedPosition = m_position;
	m_position = XYCoord(x, y);
	m_renderDirty = true;
}

void Entity::SetPosition(XYCoord newPosition)
{
	newPosition.m_x = clamp(newPosition.m_x, 1, SCREEN_WIDTH - m_width - 2);
	newPosition.m_y = clamp(newPosition.m_y, 1, SCREEN_HEIGHT - m_height - 2);

	m_lastRenderedPosition = m_position;
	m_position = newPosition;
	m_renderDirty = true;
}

void Entity::SetRenderDirty(bool dirty)
{
	m_renderDirty = dirty;
}

ScreenRegion Entity::GetLastRenderRegion()
{
	ScreenRegion result(
		m_lastRenderedPosition.m_x + 1,
		m_lastRenderedPosition.m_x + m_width,
		m_lastRenderedPosition.m_y + 1,
		m_lastRenderedPosition.m_y + m_height
	);

	return result;
}

ScreenRegion Entity::GetRenderRegion()
{
	ScreenRegion result(
		m_position.m_x + 1,
		m_position.m_x + m_width,
		m_position.m_y + 1,
		m_position.m_y + m_height
	);

	return result;
}
