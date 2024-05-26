#include "Fly.h"

// 'enemy_fly', 16x15px
uint8_t texture_enemy_fly [] = 
{
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0xff, 0xff, 
	0xff, 0xff, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x84, 0x10, 0xff, 0xff, 
	0xff, 0xff, 0x84, 0x10, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0xff, 0xff, 
	0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0xff, 0xff, 
	0xff, 0xff, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 
	0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x84, 0x10, 0x02, 0x4f, 
	0x02, 0x4f, 0x84, 0x10, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 
	0xff, 0xff, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x42, 0x08, 
	0x42, 0x08, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0x42, 0x08, 0x42, 0x08, 0x02, 0x4f, 
	0x02, 0x4f, 0x42, 0x08, 0x42, 0x08, 0x84, 0x10, 0x42, 0x08, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0x42, 0x08, 0x02, 0x4f, 0x84, 0x10, 0x42, 0x08, 
	0x42, 0x08, 0x84, 0x10, 0x02, 0x4f, 0x42, 0x08, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x02, 0x4f, 0x84, 0x10, 
	0x84, 0x10, 0x02, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0x02, 0x4f, 0x02, 0x4f, 0x02, 0x4f, 0x02, 0x4f, 
	0x02, 0x4f, 0x02, 0x4f, 0x02, 0x4f, 0x02, 0x4f, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x10, 0x02, 0x4f, 0x23, 0xe0, 0x23, 0xe0, 0x02, 0x4f, 
	0x02, 0x4f, 0x23, 0xe0, 0x23, 0xe0, 0x02, 0x4f, 0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x02, 0x4f, 0xff, 0xff, 0x02, 0x4f, 0x23, 0xe0, 0x02, 0x4f, 
	0x02, 0x4f, 0x23, 0xe0, 0x02, 0x4f, 0xff, 0xff, 0x02, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x02, 0x4f, 0x02, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x02, 0x4f, 0x02, 0x4f, 
	0x02, 0x4f, 0x02, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x02, 0x4f, 0x02, 0x4f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x02, 0x4f, 0xff, 0xff, 0xff, 0xff, 0x02, 0x4f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x02, 0x4f, 0xff, 0xff, 0xff, 0xff, 0x02, 0x4f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x02, 0x4f, 0xff, 0xff, 
	0xff, 0xff, 0x02, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

Fly::Fly()
{
	m_textureData = texture_enemy_fly;
	m_width = 16;
	m_height = 15;
}