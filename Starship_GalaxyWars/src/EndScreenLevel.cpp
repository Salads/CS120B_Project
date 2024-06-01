#include "EndScreenLevel.h"
#include "GUIMenuConfigs.h"
#include "SerialMonitor.h"

EndScreenLevel::EndScreenLevel()
{
	m_label = new TextRenderObject();
	m_label->SetText("Victory!");

	int xPos = (SCREEN_WIDTH / 2) - (m_label->GetWidth() / 2);
	int yPos = (SCREEN_HEIGHT / 4);
	m_label->SetPosition(xPos, yPos);

	m_menu = new GUIMenu(kEndScreenConfig);
	int xPos2 = (SCREEN_WIDTH / 2) - (m_menu->GetWidth() / 2);
	int yPos2 = (SCREEN_HEIGHT / 2);
	m_menu->SetPosition(xPos2, yPos2 + yPos);
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
	if(m_label->GetRenderDirty())
	{
		m_label->Render();
		m_label->SetRenderDirty(false);
	}

	if(m_menu->GetRenderDirty())
	{
		m_menu->Render();
		m_menu->SetRenderDirty(false);
	}
}

DoneReason EndScreenLevel::GetDoneReason()
{
	return m_doneReason;
}
