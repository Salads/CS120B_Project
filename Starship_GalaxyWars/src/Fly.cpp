#include "Fly.h"

uint16_t texture_enemy_fly [] = 
{
	0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x8410, 0x4208, 0x8410, 0x4208, 0x8410, 0x0000, 0x0000, 0x8410, 0x4208, 0x8410, 0x4208, 0x8410, 0x0000, 0x0000, 
	0x0000, 0x8410, 0x4208, 0x8410, 0x4208, 0x8410, 0x8410, 0x0000, 0x0000, 0x8410, 0x8410, 0x4208, 0x8410, 0x4208, 0x8410, 0x0000, 
	0x8410, 0x4208, 0x8410, 0x8410, 0x8410, 0x4208, 0x8410, 0x0000, 0x0000, 0x8410, 0x4208, 0x8410, 0x8410, 0x8410, 0x4208, 0x8410, 
	0x8410, 0x8410, 0x8410, 0x8410, 0x4208, 0x8410, 0x8410, 0x024f, 0x024f, 0x8410, 0x8410, 0x4208, 0x8410, 0x8410, 0x8410, 0x8410, 
	0x0000, 0x8410, 0x4208, 0x8410, 0x8410, 0x8410, 0x8410, 0x4208, 0x4208, 0x8410, 0x8410, 0x8410, 0x8410, 0x4208, 0x8410, 0x0000, 
	0x0000, 0x0000, 0x8410, 0x4208, 0x8410, 0x4208, 0x4208, 0x024f, 0x024f, 0x4208, 0x4208, 0x8410, 0x4208, 0x8410, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x8410, 0x4208, 0x024f, 0x8410, 0x4208, 0x4208, 0x8410, 0x024f, 0x4208, 0x8410, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x024f, 0x8410, 0x8410, 0x024f, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x8410, 0x024f, 0x024f, 0x024f, 0x024f, 0x024f, 0x024f, 0x024f, 0x024f, 0x8410, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x8410, 0x024f, 0x23e0, 0x23e0, 0x024f, 0x024f, 0x23e0, 0x23e0, 0x024f, 0x8410, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x024f, 0x0000, 0x024f, 0x23e0, 0x024f, 0x024f, 0x23e0, 0x024f, 0x0000, 0x024f, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x024f, 0x024f, 0x0000, 0x0000, 0x0000, 0x024f, 0x024f, 0x024f, 0x024f, 0x0000, 0x0000, 0x0000, 0x024f, 0x024f, 0x0000, 
	0x0000, 0x0000, 0x024f, 0x0000, 0x0000, 0x024f, 0x0000, 0x0000, 0x0000, 0x0000, 0x024f, 0x0000, 0x0000, 0x024f, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x024f, 0x0000, 0x0000, 0x024f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	
};
Fly::Fly()
{
	m_textureData = texture_enemy_fly;
	m_textureDataSize = ArraySize(texture_enemy_fly);
	m_width = 16;
	m_height = 15;
}