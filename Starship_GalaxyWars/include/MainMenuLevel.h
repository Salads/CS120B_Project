#pragma once

#include "Level.h"
#include "GUIMenu.h"

class MainMenuLevel : public Level
{
public:
	MainMenuLevel();
	void Update();
	void Render();
	DoneReason GetDoneReason();

protected:
	GUIMenu*   m_menu;
	DoneReason m_doneReason = DoneReason_None;
};
