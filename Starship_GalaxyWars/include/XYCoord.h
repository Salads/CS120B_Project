#pragma once

#include "Types.h"

struct XYCoord 
{
    XYCoord() {};
    XYCoord(uint8_t x, uint8_t y) {m_x = x; m_y = y;};
    bool IsZero() {return m_x == 0 && m_y == 0;};
    XYCoord Lerp(XYCoord start, XYCoord end, float t);

    uint8_t m_x;
    uint8_t m_y;

    static XYCoord Zero;

    bool operator==(XYCoord& other) {return this->m_x == other.m_x && this->m_y == other.m_y;};
    XYCoord& operator=(const XYCoord& other){this->m_x = other.m_x; this->m_y = other.m_y; return *this;}
};

XYCoord Lerp(XYCoord min, XYCoord max, float t);
