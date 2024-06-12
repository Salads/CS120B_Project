#include "Enemy.h"
#include "SerialMonitor.h"

uint8_t Enemy::GetScoreValue()
{
	return m_scoreValue;
}

static bool idleStart = false; // Keep enemies from moving same direction at first
void Enemy::UpdateIdlePositions()
{
	m_idlePosLeft = m_position;
	m_idlePosLeft.m_x -= 3;

	m_idlePosRight = m_position;
	m_idlePosRight.m_x += 3;

	m_desiredPos = (idleStart ? m_idlePosLeft : m_idlePosRight);
	idleStart = !idleStart;
}

void Enemy::UpdateDesiredPosition()
{
	if(m_mode == EnemyMode_Idle)
	{
		if(m_position.m_x <= m_idlePosLeft.m_x && m_position.m_y <= m_idlePosLeft.m_y)
		{
			m_desiredPos = m_idlePosRight;
		}
		else if(m_position.m_x >= m_idlePosRight.m_x && m_position.m_y >= m_idlePosRight.m_y)
		{
			m_desiredPos = m_idlePosLeft;
		}
	}
}

XYCoord Enemy::GetDesiredPos()
{
	return m_desiredPos;
}

