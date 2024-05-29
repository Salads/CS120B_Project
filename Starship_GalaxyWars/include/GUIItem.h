#pragma once

#include "TextTextures.h"
#include "XYCoord.h"
#include "Entity.h"

struct GUIItem : public Entity
{
public:
	GUIItem() = delete;
	GUIItem(TextTexture *texture);
};
