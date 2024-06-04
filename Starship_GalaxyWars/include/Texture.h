#pragma once

#include <stdint.h>
#include "TextureFormat.h"

struct Texture
{
	const uint8_t* data;
	uint16_t  	   dataSize;
	uint16_t  	   width;
	uint16_t  	   height;
	TextureFormat  textureFormat;
};
