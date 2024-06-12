#pragma once

#include "Level.h"
#include "GUIMenu.h"

class HighScoreLevel : public Level
{
public:
	HighScoreLevel();
	~HighScoreLevel();
	void Update();
	void Render();
	DoneReason GetDoneReason();
private:
	TextRenderObject* m_highScoreTexts[5];
	uint8_t 		  m_numHighScoreTexts = 0;
	GUIMenu*		  m_menu;
	DoneReason 		  m_doneReason = DoneReason_None;
};
