#include "MainMenuLevel.h"
#include "GUIMenuConfigs.h"
#include "GUIMenu.h"
#include "SerialMonitor.h"

MainMenuLevel::MainMenuLevel()
{
	// If I don't put this here, this gets optimized out when we go from end screen to main menu. siiiiiigh
	// It can't be an empty string either. SIIIIIIIGH
	// At least it's "loading" code, so it doesn't affect performance.
	Debug_PrintLine("MainMenuLevel() - Creating new GUIMenu");
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
