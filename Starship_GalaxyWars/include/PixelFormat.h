#pragma once

#include <stdint.h>

enum PixelFormat : uint8_t
{
	PixelFormat_12BitPixels = 3, // RGB = (4,4,4)
	PixelFormat_16BitPixels = 5, // RGB = (5,6,5)
	PixelFormat_18BitPixels = 6, // RGB = (6,6,6)
};
