#pragma once

#include <stdint.h>

enum TextureFormat : uint8_t
{
	TextureFormat_1Bit, // (1), white or black
	TextureFormat_16Bit // (5,6,5)
};
