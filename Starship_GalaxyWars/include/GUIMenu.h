#pragma once

#include <stdint.h>
#include "BaseRenderObject.h"
#include "Texture.h"
#include "GUIMenuConfig.h"
#include "TextRenderObject.h"

struct GUIMenu : public BaseRenderObject
{
public:
	GUIMenu(const GUIMenuConfig& config);
	~GUIMenu();
	void 	SelectPreviousOption();
	void 	SelectNextOption();
	uint8_t GetSelectedOptionIdx();
	bool	GetAcceptedSelection();
	uint8_t GetCursorLessSpace(); // Gets the width of the gap between the text options and left edge of container.
	void	Update();
	void 	Render(bool clearLastPosition = true);

private:
	void OnSetPosition();
	void UpdateLayout();

protected:
	uint8_t   			m_selectedIdx = 0;
	bool				m_acceptedSelection = false;

	Texture   		    m_cursorTexture;
	SimpleRenderObject* m_cursor;
	
	TextRenderObject*   m_textObjects[5];
	uint8_t   		    m_optionXPosition = 0;
	uint8_t   		    m_optionYPositions[5];
	uint8_t   		    m_numOptions = 0;
	uint8_t				m_largestOptionWidth = 0;
};
