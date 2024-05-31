#pragma once

#include <stdint.h>
#include "Texture.h"

struct GUIMenuConfig
{
	const char*  m_optionTexts[5];
	uint8_t      m_numOptions;

	uint8_t      m_frameWidth;
	uint8_t  	 m_frameHeight;
};
