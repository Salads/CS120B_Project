#pragma once 

#include "ST7735SClient.h"
#include "SerialMonitor.h"
#include "Entity.h"
#include "ColorUtil.h"
#include <avr/pgmspace.h>

ST7735SClient::ST7735SClient()
{
	m_screenRegion = { 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT };
}

ST7735SClient& ST7735SClient::Get()
{
	static ST7735SClient instance;
	if(!instance.GetIsInitialized()) {instance.Initialize();}
	return instance;
}

void ST7735SClient::Initialize()
{
	// Hardware Reset
	SetHardwareResetPin(0);
	_delay_ms(125);
	SetHardwareResetPin(1);
	_delay_ms(125);

	SendCommand(SWRESET); // Software Reset
	_delay_ms(125);
	SendCommand(SLPOUT); // Disable Sleep, Enable booster
	_delay_ms(125);
	SendCommand(IDMOFF); // Disable Idle Mode
	SendCommand(COLMOD); // Set Pixel Format
	SendData(PixelFormat_16BitPixels);

	SendCommand(MADCTL);
	SendData(0b00001000);

	SendCommand(DISPON); // Turn on Display

	// Clear screen and draw background
	ScreenRegion fullScreenRegion;
	SetRegion(fullScreenRegion);
	FillCurrentScreenRegionPacked16(m_backgroundColor);

	m_initialized = true;
}

void ST7735SClient::SetRegion(ScreenRegion& region)
{

	region.m_startX = clamp(region.m_startX, 1, m_screenWidth - 1);
	region.m_startY = clamp(region.m_startY, 1, m_screenHeight - 1);
	region.m_endX = clamp(region.m_endX, 1, m_screenWidth - 1);
	region.m_endY = clamp(region.m_endY, 1, m_screenHeight - 1);

	// Set Column
	uint8_t xMin = region.m_startX;
	uint8_t xMax = region.m_endX;
	SendCommand(CASET);
	SendData(0); SendData(xMin); // col start
	SendData(0); SendData(xMax); // col end 

	// Set Row
	uint8_t yMin = region.m_startY;
	uint8_t yMax = region.m_endY;
	SendCommand(RASET);
	SendData(0); SendData(yMin); // row start (high, low)
	SendData(0); SendData(yMax); // row end (high, low)

	m_screenRegion = {xMin, xMax, yMin, yMax};
}

void ST7735SClient::FillCurrentScreenRegionRGB24(uint8_t r, uint8_t g, uint8_t b)
{
	SendCommand(RAMWR);

	r = RangeMap(0, 255, 0, 0b11111,  r);
	g = RangeMap(0, 255, 0, 0b111111, g);
	b = RangeMap(0, 255, 0, 0b11111,  b);

	uint16_t color = 0;
	color = (r << 11 | g << 5 | b);

	uint16_t y = 0;
	uint16_t x = 0;

	for(y = m_screenRegion.m_startY; y <= m_screenRegion.m_endY; y++)
	{
		for(x = m_screenRegion.m_startX; x <= m_screenRegion.m_endX; x++)
		{
			SendData(color >> 8);
			SendData(color);
		}
	}
}

void ST7735SClient::FillCurrentScreenRegionPacked16(uint16_t color)
{
	SendCommand(RAMWR);

	uint8_t r = color & 0b1111100000000000 >> 11;
	uint8_t g = color & 0b0000011111100000 >> 5;
	uint8_t b = color & 0b0000000000011111;
	uint16_t newColor = (r >> 11 | g | b << 11);

	for(uint16_t y = m_screenRegion.m_startY; y <= m_screenRegion.m_endY; y++)
	{
		for(uint16_t x = m_screenRegion.m_startX; x <= m_screenRegion.m_endX; x++)
		{
			SendData(newColor >> 8);
			SendData(newColor);
		}
	}
}

void ST7735SClient::FillCurrentScreenRegionTexture(const uint8_t* textureData, uint16_t textureDataSize, TextureFormat textureFormat, uint8_t	width, uint8_t height)
{
	uint16_t arrSize = textureDataSize;
	if (arrSize <= 0) {return;}

	SendCommand(RAMWR);

	if(textureFormat == TextureFormat_16Bit)
	{
		for(uint16_t i = 0; i < arrSize; i++)
		{
			uint16_t pixel = pgm_read_word(textureData + (i*2));
			SendData(pixel >> 8);
			SendData(pixel);
		}
	}
	else if(textureFormat == TextureFormat_1Bit)
	{
		uint16_t numPixels = width * height;
		uint16_t numPixelsProcessed = 0;

		for(uint16_t i = 0; i < arrSize; i++)
		{
			if(numPixelsProcessed >= numPixels) break;

			uint8_t byte = pgm_read_byte(textureData + i);
			for(int8_t j = 7; j >= 0; j--)
			{
				if(numPixelsProcessed >= numPixels) break;

				bool pixelWhite = byte & (1 << j);
				uint16_t pixel = (pixelWhite ? 0xFFFF : m_backgroundColor);
				SendData(pixel >> 8);
				SendData(pixel);
				
				numPixelsProcessed++;
			}
		}
	}	
}

void ST7735SClient::SetHardwareResetPin(bool val)
{
	PORTB = SetBit(PORTB, PORTB4, val);
}

void ST7735SClient::SendCommand(uint8_t command)
{
	PORTB = SetBit(PORTB, PORTB1, 0);
	SPI_SEND(command);
}

void ST7735SClient::SendData(uint8_t data)
{
	PORTB = SetBit(PORTB, PORTB1, 1);
	SPI_SEND(data);
}
