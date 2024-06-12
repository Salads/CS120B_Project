#include "EndScreenLevel.h"
#include "GUIMenuConfigs.h"
#include "SerialMonitor.h"
#include "GameState.h"

EndScreenLevel::EndScreenLevel(DoneReason reason)
{
	Debug_PrintLine("EndScreenLevel::EndScreenLevel()");
	m_label = new TextRenderObject();
	bool isVictory = reason == DoneReason_Lvl1GameOverVictory || reason == DoneReason_Lvl2GameOverVictory;
	m_label->SetText(isVictory ? "Victory!" : "Defeat");

	int xPos = (SCREEN_WIDTH / 2) - (m_label->GetWidth() / 2);
	int yPos = (SCREEN_HEIGHT / 4);
	m_label->SetPosition(xPos, yPos);
	m_label->SetInitialized();

	m_menu = new GUIMenu();
	m_menu->AddOption("Continue");
	uint8_t xMenuPos = (SCREEN_WIDTH / 2) - (m_menu->GetWidth() / 2);
	uint8_t yMenuPos = SCREEN_HEIGHT / 2;
	m_menu->SetPosition(xMenuPos, yMenuPos);
	m_menu->SetInitialized();

	GameState& gameState = GameState::Get();
	gameState.InsertScore(gameState.m_score);
	gameState.SaveHighScores();
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

		GameState& gameState = GameState::Get();
		gameState.m_playerLives = 0;
		gameState.m_score = 0;
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
