#pragma once

#include "Level.h"
#include "GUIMenu.h"

class MainMenuLevel : public Level
{
public:
	MainMenuLevel();
	~MainMenuLevel();
	void Update();
	void Render();
	DoneReason GetDoneReason();

protected:
	SimpleRenderObject* m_titleImage;
	GUIMenu*   			m_menu;
	DoneReason 			m_doneReason = DoneReason_None;
};
