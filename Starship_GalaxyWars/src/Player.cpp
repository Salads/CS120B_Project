#include "Player.h"
#include "SerialMonitor.h"

// 'player_red', 14x12px
uint16_t texture_player_red [] = 
{
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 
	0x0000, 0x0000, 0x0000, 0xffff, 0xf800, 0xf800, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 
	0x0000, 0xf800, 0x8410, 0x4208, 0xf800, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xf800, 0xf800, 0x0000, 0xffff, 0x0000, 0xf800, 
	0x8410, 0x8410, 0xf800, 0x0000, 0xffff, 0x0000, 0xf800, 0xf800, 0xf800, 0xffff, 0x0000, 0xffff, 0x0000, 0xf800, 0x4208, 0x8410, 
	0xf800, 0x0000, 0xffff, 0x0000, 0xffff, 0xf800, 0xffff, 0xf800, 0xf800, 0xffff, 0x0000, 0xf800, 0xf800, 0xf800, 0xf800, 0x0000, 
	0xffff, 0xf800, 0xf800, 0xffff, 0xffff, 0xf800, 0xffff, 0xffff, 0xffff, 0xffff, 0xf800, 0xf800, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xf800, 0xffff, 0xffff, 0xffff, 0xf800, 0xffff, 0xffff, 0xffff, 0xf800, 0xf800, 0xffff, 0xffff, 0xffff, 0xf800, 0xffff, 0xffff, 
	0x0000, 0xffff, 0xffff, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xffff, 0xffff, 0x0000, 0x0000, 0xf800, 
	0xf800, 0xf800, 0xffff, 0xf800, 0xf800, 0xf800, 0xf800, 0xffff, 0xf800, 0xf800, 0xf800, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 
	0xffff, 0xffff, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x4208, 
	0x0000, 0x0000, 0x4208, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000
};

Player::Player()
{
	m_texture = texture_player_red;
	m_textureSize = ArraySize(texture_player_red);
	m_width = 14;
	m_height = 12;
}