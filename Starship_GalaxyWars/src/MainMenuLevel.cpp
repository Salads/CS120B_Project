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

	uint8_t xMenuPos = (SCREEN_WIDTH / 2) - (m_menu->GetWidth() / 2);
	uint8_t yMenuPos = (SCREEN_HEIGHT / 4);
	m_menu->SetPosition(xMenuPos, yMenuPos);
	m_menu->SetInitialized();
}

MainMenuLevel::~MainMenuLevel()
{
	if(m_menu)
	{
		delete m_menu;
	}
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
