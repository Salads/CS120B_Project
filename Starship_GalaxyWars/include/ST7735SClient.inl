#pragma once 

#include "ST7735SClient.h"
#include "SerialMonitor.h"
#include "Entity.h"
#include "ColorUtil.h"

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
	FillCurrentScreenRegion(m_backgroundColor);

	m_initialized = true;
}

void ST7735SClient::SetRegion(ScreenRegion& region)
{
	if(region.m_endX > m_screenWidth - 1 || region.m_endY > m_screenHeight - 1)
	{
		region.m_endX = m_screenWidth - 1;
		region.m_endY = m_screenHeight - 1;
	}

	// Set Column
	uint8_t xMin = region.m_startX;
	uint8_t xMax = region.m_endX;
	SendCommand(CASET);
	SendData(0); SendData(xMin); // col start
	SendData(0); SendData(xMax); // col end 

	// _delay_ms(500);

	// Set Row
	uint8_t yMin = region.m_startY;
	uint8_t yMax = region.m_endY;
	SendCommand(RASET);
	SendData(0); SendData(yMin); // row start (high, low)
	SendData(0); SendData(yMax); // row end (high, low)

	m_screenRegion = {xMin, xMax, yMin, yMax};
}

void ST7735SClient::FillCurrentScreenRegion(uint8_t r, uint8_t g, uint8_t b)
{
	SendCommand(RAMWR);

	r = RangeMap(0, 255, 0, 0b11111,  r);
	g = RangeMap(0, 255, 0, 0b111111, g);
	b = RangeMap(0, 255, 0, 0b11111,  b);

	uint16_t color = 0;
	color = (r << 11 | g << 5 | b);

	for(int y = m_screenRegion.m_startY; y < m_screenRegion.m_endY; y++)
	{
		for(int x = m_screenRegion.m_startX; x < m_screenRegion.m_endX; x++)
		{
			SendData(color >> 8);
			SendData(color);
		}
	}
}

void ST7735SClient::FillCurrentScreenRegion(uint16_t color)
{
	FillCurrentScreenRegion(color & 0b1111100000000000 >> 11, color & 0b0000011111100000 >> 5, color & 0b0000000000011111);
}

void ST7735SClient::RenderEntity(Entity* entity, bool debugRegions)
{
	// Render over previous position with background color.
	ScreenRegion lastRegion = entity->GetLastRenderRegion();
	SetRegion(lastRegion);
	FillCurrentScreenRegion(m_backgroundColor);

	// Render new position
	ScreenRegion newRegion = entity->GetRenderRegion();
	SetRegion(newRegion);
	FillCurrentScreenRegion(entity->GetTextureData(), entity->GetTextureDataSize());

	if(debugRegions)
	{
		Debug_PrintLine("{%-3d, %-3d, %-3d, %-3d} -> {%-3d, %-3d, %-3d, %-3d}", 
			lastRegion.m_startX, lastRegion.m_endX,
			lastRegion.m_startY, lastRegion.m_endY,
			newRegion.m_startX , newRegion.m_endX,
			newRegion.m_startY , newRegion.m_endY);
	}
}

void ST7735SClient::FillCurrentScreenRegion(uint16_t* data, uint16_t dataSize)
{
	uint16_t arrSize = dataSize;
	if (arrSize <= 0) {return;}

	SendCommand(RAMWR);
	for(uint16_t i = 0; i < arrSize; i++)
	{
		/*
			RGB is actually BGR. Maybe it has to do with endianness.. Oh well.
			I set MADCTL to use BGR so I don't have to software-convert the pixel data.

			Below code is for when panel is set to RGB(but actually BGR)

			uint16_t pixel = data[i];
			uint8_t red   = (pixel & 0b1111100000000000) >> 11;
			uint8_t green = (pixel & 0b0000011111100000) >> 5;
			uint8_t blue  = (pixel & 0b0000000000011111) >> 0;

			uint8_t sendByte = 0x00;

			sendByte = (blue << 3) | (green & 0b111000) >> 3;
			SendData(sendByte);

			sendByte = (green & 0b000111 << 5) | red;
			SendData(sendByte);
		*/

		uint16_t pixel = data[i];
		SendData(pixel >> 8);
		SendData(pixel);
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
