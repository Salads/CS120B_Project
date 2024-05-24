
#include "Entity.h"
#include "Globals.h"

bool Entity::GetCollides(Entity &other)
{
	// simple "box" collision checking
	// it's just an arcade game
	uint8_t this_x1 = m_posX;
	uint8_t this_x2 = m_posX + m_width;
	uint8_t this_y1 = m_posY;
	uint8_t this_y2 = m_posY + m_height;

	uint8_t other_x1 = other.m_posX;
	uint8_t other_x2 = other.m_posX + other.m_width;
	uint8_t other_y1 = other.m_posY;
	uint8_t other_y2 = other.m_posY + other.m_height;

	return (this_x1 < other_x1 && other_x1 < this_x2) || (other_x1 < this_x1 && this_x1 < other_x2) || 
		   (this_y1 < other_y1 && other_y1 < this_y2) || (other_y1 < this_y1 && this_y1 < other_y2);
}
