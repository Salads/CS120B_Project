#pragma once

#include "Level.h"
#include "GUIMenu.h"
#include "TextRenderObject.h"

class EndScreenLevel : public Level
{
public:
	EndScreenLevel(DoneReason reason);
	~EndScreenLevel();
	void Update();
	void Render();
	DoneReason GetDoneReason();
private:
	DoneReason 		  m_doneReason = DoneReason_None;

	TextRenderObject* m_label;
	GUIMenu*   		  m_menu;
};
