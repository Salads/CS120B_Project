#pragma once

#include "Globals.h"

// oh boy, here comes the pain

// [0-7] PORTD (8bit)
// [8-13] PORTB (6bit)
// [A0-A5] PORTC (6bit)
// Output: DDR=1, PORT=0
// PINx: Read Input
// PORTx: Set Output

#define ST7735S_SCREEN_WIDTH  128
#define ST7735S_SCREEN_HEIGHT 128
#define ST7735S_FRAMESIZE = ST7735S_SCREEN_WIDTH * ST7735S_SCREEN_HEIGHT


#define ST7735S_PIN_LED   PORTC0
#define ST7735S_PIN_SCK   PORTB7
#define ST7735S_PIN_SDA   PORTB5
#define ST7735S_PIN_A0    PORTC3
#define ST7735S_PIN_RESET PORTC4
#define ST7735S_PIN_CS    PORTC5

enum ST7735SCommands : uint8_t
{
	// System Functions
	NOP       = 0x00,
	SWRESET   = 0x01, /* Software Reset */
	RDDID     = 0x04, /* Read Display ID */
	RDDST     = 0x09, /* Read Display Status */
	RDDPM     = 0x0a, /* Read Display Power Mode */
	RDDMADCTL = 0x0b, /* Read Display MADCTL */
	RDDCOLMOD = 0x0c, /* Read Display Pixel Format */
	RDDIM     = 0x0d, /* Read Display Image Mode */
	RDDSM     = 0x0e, /* Read Display Signal Mode */
	RDDSDR    = 0x0f, /* Read Display Self-Diagnostic Result */
	SLPIN     = 0x10, /* Sleep In */
	SLPOUT    = 0x11, /* Sleep Out */
	PTLON     = 0x12, /* Partial Display Mode On */
	NORON     = 0x13, /* Normal Display Mode On */
	INVOFF    = 0x20, /* Display Inversion Off */
	INVON     = 0x21, /* Display Inversion On */
	GAMSET    = 0x26, /* Gamma Set */
	DISPOFF   = 0x28, /* Display Off */
	DISPON    = 0x29, /* Display On */
	CASET     = 0x2a, /* Column Address Set */
	RASET     = 0x2b, /* Row Address Set */
	RAMWR     = 0x2c, /* Memory Write */
	RGBSET    = 0x2d, /* Color Setting 4k, 65k, 262k */
	RAMRD     = 0x2e, /* Memory Read */
	PTLAR     = 0x30, /* Partial Area */
	SCRLAR    = 0x33, /* Scroll Area Set */
	TEOFF     = 0x34, /* Tearing Effect Line OFF */
	TEON      = 0x35, /* Tearing Effect Line ON */
	MADCTL    = 0x36, /* Memory Data Access Control */
	VSCSAD    = 0x37, /* Vertical Scroll Start Address of RAM */
	IDMOFF    = 0x38, /* Idle Mode Off */
	IDMON     = 0x39, /* Idle Mode On */
	COLMOD    = 0x3a, /* Interface Pixel Format */
	RDID1     = 0xda, /* Read ID1 Value */
	RDID2     = 0xdb, /* Read ID2 Value */
	RDID3     = 0xdc, /* Read ID3 Value */

	// Panel Functions
	FRMCTR1   = 0xb1, /* Frame Rate Control in normal mode, full colors */
	FRMCTR2   = 0xb2, /* Frame Rate Control in idle mode, 8 colors */
	FRMCTR3   = 0xb3, /* Frame Rate Control in partial mode, full colors */
	INVCTR    = 0xb4, /* Display Inversion Control */
	PWCTR1    = 0xc0, /* Power Control 1 */
	PWCTR2    = 0xc1, /* Power Control 2 */
	PWCTR3    = 0xc2, /* Power Control 3 in normal mode, full colors */
	PWCTR4    = 0xc3, /* Power Control 4 in idle mode 8colors */
	PWCTR5    = 0xc4, /* Power Control 5 in partial mode, full colors */
	VMCTR1    = 0xc5, /* VCOM Control 1 */
	VMOFCTR   = 0xc7, /* VCOM Offset Control */
	WRID2     = 0xd1, /* Write ID2 Value */
	WRID3     = 0xd2, /* Write ID3 Value */
	NVFCTR1   = 0xd9, /* NVM Control Status */
	NVFCTR2   = 0xde, /* NVM Read Command */
	NVFCTR3   = 0xdf, /* NVM Write Command */
	GMCTRP1   = 0xe0, /* Gamma '+'Polarity Correction Characteristics Setting */
	GMCTRN1   = 0xe1, /* Gamma '-'Polarity Correction Characteristics Setting */
	GCV       = 0xfc, /* Gate Pump Clock Frequency Variable */
};

/* columns: 1 = # of params, 2 = command, 3 .. = params */
static uint8_t init_cmd[] = {
    1, SWRESET, /* software reset */
    1,  SLPOUT, /* sleep out, turn off sleep mode */
	1, DISPOFF,  /*  output from frame mem disabled */
    4, FRMCTR1, 0x00, 0b111111, 0b111111, /* frame frequency normal mode (highest frame rate in normal mode) */
    4, FRMCTR2, 0b1111, 0x01, 0x01, /* frame frequency idle mode */
    7, FRMCTR3, 0x05, 0x3c, 0x3c, 0x05, 0x3c, 0x3c,  /* frame freq partial mode: 1-3 dot inv, 4-6 col inv */
    2,  INVCTR, 0x03, /* display inversion control: 3-bit 0=dot, 1=col */

    4,  PWCTR1, 0b11111100, 0x08, 0b10, /* power control */
    2,  PWCTR2, 0xc0,
    3,  PWCTR3, 0x0d, 0x00,
    3,  PWCTR4, 0x8d, 0x2a,
    3,  PWCTR5, 0x8d, 0xee, /* partial */

	/* display brightness and gamma */
    2,     GCV, 0b11011000, /* auto gate pump freq, max power save */
    2, NVFCTR1, 0b01000000, /* automatic adjust gate pumping clock for saving power consumption */
	2,  VMCTR1, 0b001111,  /* VCOM voltage setting */
    2, VMOFCTR, 0b10000, /* ligthness of black color 0-0x1f */
    2,  GAMSET, 0x08, /* gamma 1, 2, 4, 8 */

    2,  MADCTL, 0b01100000, /* row oder, col order, row colum xchange, vert refr order, rgb/bgr, hor refr order, 0, 0 */
    2,  COLMOD, 0x05, /* 3=12bit, 5=16-bit, 6=18-bit  pixel color mode */
    17, GMCTRP1,0x02, 0x1c, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2c,
                0x29, 0x25, 0x2b, 0x39, 0x00, 0x01, 0x03, 0x10,
    17, GMCTRN1,0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2c,
                0x2e, 0x2e, 0x37, 0x3f, 0x00, 0x00, 0x02, 0x10,
    5,   CASET, 0, 0, 0, ST7735S_SCREEN_HEIGHT - 1,
    5,   RASET, 0, 0, 0, ST7735S_SCREEN_WIDTH  - 1,
    1,   INVON, /* display inversion on/off */
    1,  IDMOFF, /* idle mode off */
    1,   NORON,  /* normal display mode on */
    1,  DISPON,  /* recover from display off, output from frame mem enabled */
};
