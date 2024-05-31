#include "MainMenuLevel.h"
#include "GUIMenuConfigs.h"
#include "GUIMenu.h"

MainMenuLevel::MainMenuLevel()
{
	m_menu = new GUIMenu(kMainMenuConfig);
	m_type = LevelType_Menu;
}

void MainMenuLevel::Update()
{
	m_menu->Update();
	if(m_doneReason == DoneReason_None && m_menu->GetAcceptedSelection())
	{
		if(m_menu->GetSelectedOptionIdx() == 0)
		{
			m_doneReason = DoneReason_StartGame;
		}
		else if(m_menu->GetSelectedOptionIdx() == 1)
		{
			m_doneReason = DoneReason_ViewHighScore;
		}
	}
}

void MainMenuLevel::Render()
{
	if(m_menu->GetRenderDirty())
	{
		m_menu->Render();
		m_menu->SetRenderDirty(false);
	}
}

DoneReason MainMenuLevel::GetDoneReason()
{
	return m_doneReason;
}
