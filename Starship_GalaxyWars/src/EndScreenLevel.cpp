#include "EndScreenLevel.h"
#include "GUIMenuConfigs.h"
#include "SerialMonitor.h"

EndScreenLevel::EndScreenLevel(DoneReason reason)
{
	m_label = new TextRenderObject();
	m_label->SetText(reason == DoneReason_GameOverVictory ? "Victory!" : "Defeat");

	int xPos = (SCREEN_WIDTH / 2) - (m_label->GetWidth() / 2);
	int yPos = (SCREEN_HEIGHT / 4);
	m_label->SetPosition(xPos, yPos);
	m_label->SetInitialized();

	m_menu = new GUIMenu(kEndScreenConfig);
	uint8_t xMenuPos = (SCREEN_WIDTH / 2) - (m_menu->GetWidth() / 2);
	uint8_t yMenuPos = SCREEN_HEIGHT / 2;
	m_menu->SetPosition(xMenuPos, yMenuPos);
	m_menu->SetInitialized();
}

EndScreenLevel::~EndScreenLevel()
{
	if(m_label)
	{
		delete m_label;
	}

	if(m_menu)
	{
		delete m_menu;
	}
}

void EndScreenLevel::Update()
{
	m_menu->Update();

	if(m_menu->GetAcceptedSelection())
	{
		m_doneReason = DoneReason_EndScreenDone;
	}
}

void EndScreenLevel::Render()
{
	m_label->Render();
	m_menu->Render();
}

DoneReason EndScreenLevel::GetDoneReason()
{
	return m_doneReason;
}
