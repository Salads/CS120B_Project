#include "HighScoreLevel.h"

const GUIMenuConfig kHighScoreMenu =
{
	{"Go Back"},
	1
};

HighScoreLevel::HighScoreLevel()
{
	GUIMenuConfig config;
	config = 
	{
		{"12", "5", "3", "1" },
		4
	};

	m_highScoreMenu = new GUIMenu(config);
	uint8_t xPos = (SCREEN_WIDTH / 2) - (m_highScoreMenu->GetWidth() / 2);
	m_highScoreMenu->SetPosition(xPos, SCREEN_HEIGHT * 0.15);
	m_highScoreMenu->SetIsDumbList();
	m_highScoreMenu->SetInitialized();

	m_menu = new GUIMenu(kHighScoreMenu);
	xPos = (SCREEN_WIDTH / 2) - (m_menu->GetWidth() / 2);
	m_menu->SetPosition(xPos, SCREEN_HEIGHT - m_menu->GetHeight() - 10);
	m_menu->SetInitialized();
}

HighScoreLevel::~HighScoreLevel()
{
	if(m_highScoreMenu) delete m_highScoreMenu;
	if(m_menu) delete m_menu;
}


void HighScoreLevel::Update()
{
	m_menu->Update();
	if(m_menu->GetAcceptedSelection())
	{
		if(m_menu->GetSelectedOptionIdx() == 0)
		{
			m_doneReason = DoneReason_HighScore_GoBack;
		}
	}
}

void HighScoreLevel::Render()
{
	m_highScoreMenu->Render();
	m_menu->Render();
}

DoneReason HighScoreLevel::GetDoneReason()
{
	return m_doneReason;
}
