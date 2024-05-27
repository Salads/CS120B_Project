#pragma once

#include "stdint.h"

uint8_t SetBit(uint8_t x, uint8_t k, uint8_t b);
uint8_t GetBit(uint8_t x, uint8_t k);

constexpr double MStoSeconds(uint32_t ms)
{
	return (double)ms / 1000.0;
};
