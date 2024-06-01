#include "TextRenderObject.h"
#include <stdint.h>
#include <string.h>
#include "TextTextures.h"
#include "ST7735SClient.h"

TextRenderObject::~TextRenderObject()
{
	for(uint8_t i = 0; i < m_textSize; i++)
	{
		delete m_renderObjects[i];
	}
	
	m_textSize = 0;
}

void TextRenderObject::Render(bool clearLastPosition)
{
	for(uint8_t i = 0; i < m_textSize; i++)
	{
		m_renderObjects[i]->Render(clearLastPosition);
	}

	SetRenderDirty(false);
}

// I don't trust string compare performance.
// Try to avoid calling this if the text isn't changed.
void TextRenderObject::SetText(const char* newText)
{
	bool textChanged = strcmp(newText, m_text);
	if (!textChanged) return;

	uint8_t totalWidth = 0;
	uint8_t totalHeight = 0;

	uint8_t newLen = strlen(newText);

	if (newLen > m_textSize)
	{
		for(uint8_t i = 0; i < newLen; i++)
		{
			Texture charTexture = GetCharTexture(newText[i]);
			if(m_renderObjects[i] == nullptr)
			{
				m_renderObjects[i] = new SimpleRenderObject(charTexture);
			}
			else
			{
				m_renderObjects[i]->SetTexture(charTexture);
			}

			totalWidth += m_renderObjects[i]->GetWidth();
			totalHeight += m_renderObjects[i]->GetHeight();
		}
	}
	else if (newLen < m_textSize)
	{
		for(uint8_t i = 0; i < newLen; i++)
		{
			Texture charTexture = GetCharTexture(newText[i]);
			m_renderObjects[i]->SetTexture(charTexture);

			totalWidth += m_renderObjects[i]->GetWidth();
			totalHeight += m_renderObjects[i]->GetHeight();
		}

		for(uint8_t i = newLen; i < m_textSize; i++)
		{
			// I would rather delete them later, but oh well.
			m_renderObjects[i]->ClearFromDisplay();
			delete m_renderObjects[i];
			m_renderObjects[i] = nullptr;
		}
	}
	else // Same string length, different contents
	{
		for(uint8_t i = 0; i < newLen; i++)
		{
			Texture charTexture = GetCharTexture(newText[i]);
			m_renderObjects[i]->SetTexture(charTexture);

			totalWidth += m_renderObjects[i]->GetWidth();
			totalHeight += m_renderObjects[i]->GetHeight();
		}
	}

	strcpy(m_text, newText);
	m_textSize = newLen;
	m_width = totalWidth;
	m_height = totalHeight;

	UpdateChildPositions();
}

void TextRenderObject::OnSetPosition()
{
	UpdateChildPositions();
}

void TextRenderObject::UpdateChildPositions()
{
	XYCoord startPosition = GetPosition();

	for(uint8_t i = 0; i < m_textSize; i++)
	{
		int16_t posX = startPosition.m_x + (i * 7);
		int16_t posY = startPosition.m_y;
		m_renderObjects[i]->SetPosition(posX, posY);
	}

	SetRenderDirty(true);
}
