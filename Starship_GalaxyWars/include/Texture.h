#pragma once

#include <stdint.h>
#include "TextureFormat.h"

struct Texture
{
	Texture()
	{
		data = nullptr;
		dataSize = 0;
		width = 0;
		height = 0;
		textureFormat = TextureFormat_16Bit;
	};

	Texture(const uint8_t* _data, uint16_t _dataSize, uint16_t _width, uint16_t _height, TextureFormat _textureFormat)
	{
		data = _data;
		dataSize = _dataSize;
		width = _width;
		height = _height;
		textureFormat = _textureFormat;
	};

	const uint8_t* data = nullptr;
	uint16_t  	   dataSize = 0;
	uint16_t  	   width = 0;
	uint16_t  	   height = 0;
	TextureFormat  textureFormat = TextureFormat_16Bit;
};
