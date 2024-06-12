#include "Combatant.h"

Combatant::Combatant()
{
	
}

bool Combatant::GetIsAlive()
{
	return m_hp > 0;
}

uint8_t Combatant::GetHP()
{
	return m_hp;
}

void Combatant::SetHP(uint8_t newHP)
{
	m_hp = newHP;
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
