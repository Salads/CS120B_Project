#pragma once 

#include "ST7735SClient.h"
#include "SerialMonitor.h"

ST7735SClient::ST7735SClient()
{
	m_screenRegion = { 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT };
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
	//_delay_ms(500);
	SendCommand(COLMOD); // Set Pixel Format
	SendData(PixelFormat_18BitPixels);
	//_delay_ms(200);
	SendCommand(DISPON); // Turn on Display
	//_delay_ms(200);
}

void ST7735SClient::SetRegion(uint8_t rowStart, uint8_t rowEnd, uint8_t colStart, uint8_t colEnd)
{
	if(rowEnd >= m_screenWidth - 1 || colEnd >= m_screenHeight - 1)
	{
		return;
	}

	// Set Column
	uint8_t xMin = rowStart;
	uint8_t xMax = rowEnd;
	SendCommand(CASET);
	SendData(0); SendData(xMin); // col start
	SendData(0); SendData(xMax); // col end 

	// _delay_ms(500);

	// Set Row
	uint8_t yMin = colStart;
	uint8_t yMax = colEnd;
	SendCommand(RASET);
	SendData(0); SendData(yMin); // row start (high, low)
	SendData(0); SendData(yMax); // row end (high, low)

	m_screenRegion = {xMin, xMax, yMin, yMax};
}

void ST7735SClient::FillCurrentScreenRegion(uint8_t r, uint8_t g, uint8_t b)
{
	// TODO(Darrell): Different Color Formats

	SendCommand(RAMWR);

	for(int y = m_screenRegion.m_startY; y < m_screenRegion.m_endY; y++)
	{
		for(int x = m_screenRegion.m_startX; x < m_screenRegion.m_endX; x++)
		{
			SendData(b);
			SendData(g);
			SendData(r);
		}
	}
}

void ST7735SClient::FillCurrentScreenRegion(uint8_t r, uint8_t g, uint8_t b, uint8_t* data)
{
	
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
