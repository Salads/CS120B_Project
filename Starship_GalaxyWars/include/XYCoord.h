#pragma once

#include "Types.h"

struct XYCoord 
{
    XYCoord() {};
    XYCoord(uint8_t x, uint8_t y) {m_x = x; m_y = y;};

    uint8_t m_x;
    uint8_t m_y;
};
