
#include "Entity.h"
#include "ScreenRegion.h"

Entity::Entity()
{
	m_lastPosition = XYCoord(0, 0);
	m_position = XYCoord(0,0);
}

bool Entity::GetCollides(Entity &other)
{
	// simple "box" collision checking
	// it's just an arcade game
	uint8_t this_x1 = m_position.m_x;
	uint8_t this_x2 = m_position.m_x + m_width;
	uint8_t this_y1 = m_position.m_y;
	uint8_t this_y2 = m_position.m_y + m_height;

	uint8_t other_x1 = other.m_position.m_x;
	uint8_t other_x2 = other.m_position.m_x + other.m_width;
	uint8_t other_y1 = other.m_position.m_y;
	uint8_t other_y2 = other.m_position.m_y + other.m_height;

	return (this_x1 < other_x1 && other_x1 < this_x2) || (other_x1 < this_x1 && this_x1 < other_x2) || 
		   (this_y1 < other_y1 && other_y1 < this_y2) || (other_y1 < this_y1 && this_y1 < other_y2);
}

void Entity::SetPosition(uint8_t x, uint8_t y)
{
	m_renderDirty = true;
	m_lastPosition = m_position;
	m_position = XYCoord(x, y);
	m_renderDirty = true;
}

void Entity::SetRenderDirty(bool dirty)
{
	m_renderDirty = dirty;
}

ScreenRegion Entity::GetLastRenderRegion()
{
	ScreenRegion result(
		m_lastPosition.m_x,
		m_lastPosition.m_x + m_width,
		m_lastPosition.m_y,
		m_lastPosition.m_y + m_height
	);

	return result;
}

ScreenRegion Entity::GetRenderRegion()
{
	ScreenRegion result(
		m_position.m_x,
		m_position.m_x + m_width,
		m_position.m_y,
		m_position.m_y + m_height
	);

	return result;
}
