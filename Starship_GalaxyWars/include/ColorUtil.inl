#include "ColorUtil.h"

uint8_t RangeMap(uint8_t srcRangeStart, uint8_t srcRangeEnd, uint8_t destRangeStart, uint8_t destRangeEnd, uint8_t srcVal)
{
    uint8_t srcRange = srcRangeEnd - srcRangeStart; // Same amount of numbers, but starts from zero.
    float srcRangePercent = srcVal / srcRange;

    uint8_t destRange = destRangeEnd - destRangeStart;
    uint8_t newVal = destRangeStart + (srcRangePercent * destRange);
    return newVal;
}

uint8_t* ConvertRGB24DataTo12(uint8_t* src)
{
    uint32_t srcSize = ArraySize(src);
    uint32_t destSize = ceil((float)srcSize / 2.0);
    uint8_t* resultData = new uint8_t[destSize];

    for (int i = 0; i < srcSize; i++)
    [

    ]

    return resultData;
}
