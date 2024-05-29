#pragma once

#include "GUIItem.h"

// GUIItem, but stiches together a texture from a number
class GUIItemNumeric : public GUIItem
{
public:
	GUIItemNumeric(uint8_t srcNum);
};
