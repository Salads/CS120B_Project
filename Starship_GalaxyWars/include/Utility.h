#pragma once

#include "stdint.h"

uint8_t SetBit(uint8_t x, uint8_t k, uint8_t b);
uint8_t GetBit(uint8_t x, uint8_t k);

constexpr double MStoSeconds(uint32_t ms)
{
	return (double)ms / 1000.0;
};

constexpr int16_t min(int16_t a, int16_t b)
{
	return (a < b ? a : b);
};

constexpr int16_t max(int16_t a, int16_t b)
{
	return (a > b ? a : b);
};

constexpr int16_t clamp(int16_t val, int16_t minVal, int16_t maxVal)
{
	return min(maxVal, max(val, minVal));
};

constexpr int16_t lerp(int16_t minVal, int16_t maxVal, float t)
{
	return minVal + (maxVal - minVal) * t;
};
