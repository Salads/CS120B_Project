#include "Enemy.h"
#include "SerialMonitor.h"

uint8_t Enemy::GetScoreValue()
{
	return m_scoreValue;
}

void Enemy::UpdateIdlePositions()
{
	m_idlePosLeft = m_position;
	m_idlePosLeft.m_x -= 5;

	m_idlePosRight = m_position;
	m_idlePosRight.m_x += 5;
}

void Enemy::UpdateDesiredPosition()
{
	if(m_mode == EnemyMode_Idle)
	{
		// Debug_PrintLine("px %d, py %d, ix %d, iy %d", 
		// 	m_position.m_x, m_position.m_y, 
		// 	m_idlePosLeft.m_x, m_idlePosLeft.m_y);

		if(m_position.m_x <= m_idlePosLeft.m_x && m_position.m_y <= m_idlePosLeft.m_y)
		{
			m_desiredPos = m_idlePosRight;
			//Debug_PrintLine("Idle Right");
		}
		else if(m_position.m_x >= m_idlePosRight.m_x && m_position.m_y >= m_idlePosRight.m_y)
		{
			m_desiredPos = m_idlePosLeft;
			//Debug_PrintLine("Idle Left");
		}
	}
}

XYCoord Enemy::GetDesiredPos()
{
	return m_desiredPos;
}

