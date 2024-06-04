#include "DebugLevel_Region.h"

#if DEBUG_REGIONS
DebugLevel_Region::DebugLevel_Region()
{
	m_bullet = new Bullet(BulletType_PlayerNormal);
	m_bullet->SetPosition(40, 40);
	m_bullet->SetInitialized();

	m_fly    = new Fly();
	m_fly->SetPosition(80, 40);
	m_fly->SetInitialized();
}

DebugLevel_Region::~DebugLevel_Region()
{
	if(m_bullet) delete m_bullet;
	if(m_fly) delete m_fly;
}

void DebugLevel_Region::Update()
{

}

void DebugLevel_Region::Render()
{
	m_bullet->Render();
	m_fly->Render();
}

DoneReason DebugLevel_Region::GetDoneReason()
{
	return DoneReason_None;
}
#endif
