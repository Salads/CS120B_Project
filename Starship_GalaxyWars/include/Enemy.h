#pragma once

#include "Types.h"
#include "Combatant.h"

class Enemy : public Combatant
{
public:
	uint8_t GetScoreValue();
protected:
	uint8_t m_scoreValue = 1;
};
