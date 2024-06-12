#pragma once

#include "Types.h"
#include "Combatant.h"

enum EnemyMode : uint8_t 
{
	EnemyMode_Idle,
	EnemyMode_Attack
};

class Enemy : public Combatant
{
public:
	uint8_t GetScoreValue();
	XYCoord GetDesiredPos();
	void	UpdateIdlePositions();
	void	UpdateDesiredPosition();

protected:
	uint8_t m_scoreValue = 1;

	XYCoord m_idlePosLeft;
	XYCoord m_idlePosRight;
	XYCoord m_desiredPos;

	EnemyMode m_mode = EnemyMode_Idle;
};
