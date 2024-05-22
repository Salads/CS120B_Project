#pragma once

#include "ST7735S.h"
#include "helper.h"
#include "spiAVR.h"

#define SCREEN_HEIGHT 160
#define SCREEN_WIDTH  128

enum PixelFormat : uint8_t
{
	PixelFormat_12BitPixels = 3, // RGB = (4,4,4)
	PixelFormat_16BitPixels = 5, // RGB = (5,6,5)
	PixelFormat_18BitPixels = 6, // RGB = (6,6,6)
};

struct ScreenRegion
{
	ScreenRegion(){};
	ScreenRegion(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1)
		: m_startX(x0), m_endX(x1), m_startY(y0), m_endY(y1) {};

	uint8_t m_startX = 0;
	uint8_t m_endX = SCREEN_WIDTH;

	uint8_t m_startY = 0;
	uint8_t m_endY = SCREEN_HEIGHT;
};

class ST7735SClient
{
public:
	FORCE_INLINE ST7735SClient();
	FORCE_INLINE void Initialize();
	FORCE_INLINE void SetRegion(uint8_t rowStart, uint8_t rowEnd, uint8_t colStart, uint8_t colEnd);
	FORCE_INLINE void FillCurrentScreenRegion(uint8_t r, uint8_t g, uint8_t b);

private:
	FORCE_INLINE void SendCommand(uint8_t);
	FORCE_INLINE void SendData(uint8_t);
	FORCE_INLINE void SetHardwareResetPin(bool val);

private:
	PixelFormat 		m_pixelFormat = PixelFormat_18BitPixels; // This is the default pixel format
	uint8_t             m_screenWidth = SCREEN_WIDTH;
	uint8_t             m_screenHeight = SCREEN_HEIGHT;

	ScreenRegion        m_screenRegion;
};

#include "ST7735SClient.inl"
