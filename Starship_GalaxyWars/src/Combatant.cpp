#include "Combatant.h"

bool Combatant::GetIsAlive()
{
	return m_hp > 0;
}

uint8_t Combatant::GetHP()
{
	return m_hp;
}

void Combatant::TakeDamage(uint8_t damage)
{
	if (damage > m_hp)
	{
		m_hp = 0;
		return;
	}

	m_hp -= damage;
}

void Combatant::FireBullet()
{
	// TODO(Darrell): Fire Bullet
}
