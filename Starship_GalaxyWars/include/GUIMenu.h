#pragma once

#include <stdint.h>
#include "BaseRenderObject.h"
#include "Texture.h"
#include "GUIMenuConfig.h"
#include "TextRenderObject.h"

#define GUIMENU_MAX_OPTIONS 5

struct GUIMenu : public BaseRenderObject
{
public:
	GUIMenu();
	~GUIMenu();
	void	AddOption(const char* newOptionText);
	void 	SelectPreviousOption();
	void 	SelectNextOption();
	uint8_t GetSelectedOptionIdx();
	bool	GetAcceptedSelection();
	void	Unlock();

	uint8_t GetCursorLessSpace(); // Gets the width of the gap between the text options and left edge of container.
	void	Update();
	void 	Render(bool clearLastPosition = true);

protected:
	void OnSetRenderDirty(bool newDirty);

private:
	void OnSetPosition();
	void UpdateLayout();

protected:
	uint8_t   			m_selectedIdx = 0;
	bool				m_acceptedSelection = false;

	SimpleRenderObject  m_cursor;
	
	TextRenderObject*   m_textObjects[GUIMENU_MAX_OPTIONS] = {nullptr};
	uint8_t   		    m_optionXPosition = 0;
	uint8_t   		    m_optionYPositions[GUIMENU_MAX_OPTIONS];
	uint8_t   		    m_numOptions = 0;
	uint8_t				m_largestOptionWidth = 0;
private:
	const uint8_t		m_borderThickness = 2;
	const uint8_t		m_borderGap		  = 5;
};
