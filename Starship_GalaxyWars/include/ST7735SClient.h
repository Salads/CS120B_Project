#pragma once

#include "ST7735S.h"
#include "SPIUtil.h"
#include "ScreenRegion.h"

enum PixelFormat : uint8_t
{
	PixelFormat_12BitPixels = 3, // RGB = (4,4,4)
	PixelFormat_16BitPixels = 5, // RGB = (5,6,5)
	PixelFormat_18BitPixels = 6, // RGB = (6,6,6)
};

class ST7735SClient
{
public:
	FORCE_INLINE ST7735SClient();
	FORCE_INLINE static ST7735SClient& Get();

	FORCE_INLINE void Initialize();
	FORCE_INLINE void SetRegion(ScreenRegion& region);
	FORCE_INLINE void FillCurrentScreenRegion(uint8_t r, uint8_t g, uint8_t b);
	FORCE_INLINE void FillCurrentScreenRegion(uint8_t r, uint8_t g, uint8_t b, uint8_t* data);
	FORCE_INLINE bool GetIsInitialized() {return m_initialized;}

private:
	FORCE_INLINE void SendCommand(uint8_t);
	FORCE_INLINE void SendData(uint8_t);
	FORCE_INLINE void SetHardwareResetPin(bool val);

private:
	bool				m_initialized = false;
	PixelFormat 		m_pixelFormat = PixelFormat_18BitPixels; // This is the default pixel format
	uint8_t             m_screenWidth = SCREEN_WIDTH;
	uint8_t             m_screenHeight = SCREEN_HEIGHT;

	ScreenRegion        m_screenRegion;
};

#include "ST7735SClient.inl"
