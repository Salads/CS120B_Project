#pragma once

#include "Types.h"
#include "Entity.h"

class Combatant : public Entity
{
public:
	Combatant();
public:
	uint8_t 		GetHP();
	bool 			GetIsAlive();
	void 			TakeDamage(uint8_t damage);
	virtual void 	FireBullet();
	void			SetHP(uint8_t newHP);

	uint32_t m_timeLastFire = 0;
protected:
	uint8_t m_hp = 1;
	uint8_t m_damage = 1;
};
