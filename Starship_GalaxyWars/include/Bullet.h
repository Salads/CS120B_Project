#pragma once

#include "Entity.h"

enum BulletType : uint8_t 
{
	BulletType_PlayerNormal,
	BulletType_PlayerNanoSlice, // Big curved purple wave
	BulletType_EnemyNormal
};

class Bullet : public Entity
{
public:
    Bullet(BulletType type);
private:
	BulletType m_bulletType;
};
