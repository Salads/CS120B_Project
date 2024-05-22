#pragma once
#include "Globals.h"

class Entity
{
public:
	bool GetCollides(Entity &other);
	virtual uint8_t* GetTextureData() = 0;
private:
	uint8_t m_width = 25;
	uint8_t m_height = 25;
	uint8_t m_posX = 0;
	uint8_t m_posY = 0;
};
