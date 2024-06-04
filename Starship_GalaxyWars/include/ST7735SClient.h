#pragma once

#include "ST7735S.h"
#include "SPIUtil.h"
#include "ScreenRegion.h"
#include "Entity.h"
#include "PixelFormat.h"

class ST7735SClient
{
public:
	FORCE_INLINE ST7735SClient();
	FORCE_INLINE static ST7735SClient& Get();

	FORCE_INLINE void Initialize();
	FORCE_INLINE void SetRegion(ScreenRegion& region);
	FORCE_INLINE void FillCurrentScreenRegionRGB24(uint8_t r, uint8_t g, uint8_t b);
	FORCE_INLINE void FillCurrentScreenRegionPacked16(uint16_t color);
	FORCE_INLINE void FillCurrentScreenRegionTexture(const uint8_t* textureData, uint16_t textureDataSize, TextureFormat textureFormat, uint8_t	width, uint8_t height);
	FORCE_INLINE bool GetIsInitialized() {return m_initialized;}

private:
	FORCE_INLINE void SendCommand(uint8_t);
	FORCE_INLINE void SendData(uint8_t);
	FORCE_INLINE void SetHardwareResetPin(bool val);

public:
	uint16_t            m_backgroundColor = 0x00;

private:
	bool				m_initialized = false;
	PixelFormat 		m_pixelFormat = PixelFormat_18BitPixels; // This is the default pixel format
	uint8_t             m_screenWidth = SCREEN_WIDTH;
	uint8_t             m_screenHeight = SCREEN_HEIGHT;

	ScreenRegion        m_screenRegion;
};

#include "ST7735SClient.inl"
