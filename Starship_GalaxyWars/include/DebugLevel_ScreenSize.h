#pragma once

#include "TextRenderObject.h"
#include "Level.h"

#if DEBUG_SCREENSIZE
struct DebugLevel_ScreenSize : public Level
{
public:
	DebugLevel_ScreenSize();
	void Update();
	void Render();
	DoneReason GetDoneReason();

private:
	TextRenderObject* m_text;
	uint8_t           m_debugWidthLast  = 0;
	uint8_t			  m_debugHeightLast = 0;
	uint8_t           m_debugWidth  = 0;
	uint8_t			  m_debugHeight = 0;
};
#endif

