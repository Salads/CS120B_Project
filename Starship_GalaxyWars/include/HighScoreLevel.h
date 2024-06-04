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
	GUIMenu* m_highScoreMenu;
	GUIMenu* m_menu;
	DoneReason m_doneReason = DoneReason_None;
};
