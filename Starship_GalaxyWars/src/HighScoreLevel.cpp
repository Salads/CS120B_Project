#include "HighScoreLevel.h"
#include "GameState.h"

HighScoreLevel::HighScoreLevel()
{
	Debug_PrintLine("HighScoreLevel::HighScoreLevel()");
	GameState& gameState = GameState::Get();
	gameState.LoadHighScores();

	// Add high scores
	for(uint8_t i = 0; i < gameState.m_numScores; i++)
	{
		char scoreText[11];
		sprintf(scoreText, "%d: %d", i + 1, gameState.m_scores[i]);
		m_highScoreTexts[i] = new TextRenderObject();
		m_highScoreTexts[i]->SetText(scoreText);
		m_numHighScoreTexts++;

		uint8_t xPos = (SCREEN_WIDTH / 2) - (m_highScoreTexts[i]->GetWidth() / 2);
		m_highScoreTexts[i]->SetPosition(xPos, 20 + (i * 10));
		m_highScoreTexts[i]->SetInitialized();
	}

	if(gameState.m_numScores == 0)
	{
		m_highScoreTexts[0] = new TextRenderObject();
		m_highScoreTexts[0]->SetText("<empty>");
		uint8_t xPos = (SCREEN_WIDTH / 2) - (m_highScoreTexts[0]->GetWidth() / 2);
		m_highScoreTexts[0]->SetPosition(xPos, 20 + (0 * 10));
		m_highScoreTexts[0]->SetInitialized();
		m_numHighScoreTexts++;
	}

	m_menu = new GUIMenu();
	m_menu->AddOption("Go Back");
	uint8_t xPos = (SCREEN_WIDTH / 2) - (m_menu->GetWidth() / 2);
	m_menu->SetPosition(xPos, SCREEN_HEIGHT - m_menu->GetHeight() - 10);
	m_menu->SetInitialized();
}

HighScoreLevel::~HighScoreLevel()
{
	if(m_menu) delete m_menu;

	for(int i = 0; i < m_numHighScoreTexts; i++)
	{
		delete m_highScoreTexts[i];
	}
}


void HighScoreLevel::Update()
{
	m_menu->Update();

	if(m_doneReason == DoneReason_None && m_menu->GetAcceptedSelection())
	{
		if(m_menu->GetSelectedOptionIdx() == 0)
		{
			m_doneReason = DoneReason_HighScore_GoBack;
		}
	}
}

void HighScoreLevel::Render()
{
	m_menu->Render();

	for(int i = 0; i < m_numHighScoreTexts; i++)
	{
		m_highScoreTexts[i]->Render();
	}
}

DoneReason HighScoreLevel::GetDoneReason()
{
	return m_doneReason;
}
