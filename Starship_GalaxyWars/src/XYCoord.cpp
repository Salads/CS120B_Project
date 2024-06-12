#include "XYCoord.h"
#include "Utility.h"

XYCoord Lerp(XYCoord min, XYCoord max, float t)
{
	XYCoord result;
	result.m_x = clamp(min.m_x + (max.m_x - min.m_x) * t, min.m_x, max.m_x);
	result.m_y = clamp(min.m_y + (max.m_y - min.m_y) * t, min.m_y, max.m_y);

	return result;
}
