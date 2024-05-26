#include "Bullet.h"

Bullet::Bullet(BulletType type)
{
	switch(type)
	{
		case BulletType_PlayerNormal:
			m_textureData = texture_player_bullet;
			m_width = 2;
			m_height = 4;
			break;
		case BulletType_PlayerNanoSlice:
			m_textureData = texture_player_nanoslice;
			m_width = 16;
			m_height = 5;
		case BulletType_EnemyNormal:
			m_textureData = texture_enemy_bullet;
			m_width = 2;
			m_height = 4;
	}
}
