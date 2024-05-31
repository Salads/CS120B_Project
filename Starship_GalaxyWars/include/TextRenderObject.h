#pragma once

#include "BaseRenderObject.h"
#include "SimpleRenderObject.h"

#define MAX_STR_LEN 25

extern Texture kFullFontTexture;

class TextRenderObject : public BaseRenderObject
{
public:
	void Render(bool clearLastPosition = true);
	void SetText(const char* newText);

protected:
	void OnSetPosition();

private:
	void UpdateChildPositions();

protected:
	char      		    m_text[MAX_STR_LEN];
	SimpleRenderObject* m_renderObjects[MAX_STR_LEN] = {nullptr};
	uint8_t   		    m_textSize;
};
