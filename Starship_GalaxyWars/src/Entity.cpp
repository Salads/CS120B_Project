
#include "Entity.h"
#include "ScreenRegion.h"
#include "ST7735SClient.h"

Entity::Entity() {}

Entity::Entity(Texture& texture) 
	: SimpleRenderObject(texture)
{}

Entity::~Entity()
{
	
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
