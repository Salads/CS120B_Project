#pragma once

// This file contains the interface for conveniently converting full 24bit RGB color into a 4-4-4 12bit color

// Maps a value from a source range to another range.
// Range start and ends are inclusive, and assumes int-like values.
FORCE_INLINE uint8_t RangeMap(uint8_t srcRangeStart, uint8_t srcRangeEnd, uint8_t destRangeStart, uint8_t destRangeEnd, uint8_t srcVal);

FORCE_INLINE uint8_t* ConvertRGB24DataTo12(uint8_t* src);

#include "ColorUtil.inl"
