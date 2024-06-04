#pragma once

#include "Level.h"
#include "Bullet.h"
#include "Fly.h"

#if DEBUG_REGIONS
class DebugLevel_Region : public Level
{
public:
	DebugLevel_Region();
	~DebugLevel_Region();
	void Update();
	void Render();
	DoneReason GetDoneReason();

private:
	Bullet*	m_bullet;
	Fly   * m_fly;
};
#endif
