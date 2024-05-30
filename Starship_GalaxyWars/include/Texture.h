#pragma once

#include <stdint.h>

struct Texture
{
	const uint16_t* data;
	uint16_t  dataSize;
	uint16_t  width;
	uint16_t  height;
};
