#pragma once

#include "TextTextures.h"
#include "XYCoord.h"
#include "Entity.h"

struct GUIItem : public TextRenderObject
{
public:
	GUIItem() = delete;
	GUIItem(TextTexture *texture);
};
