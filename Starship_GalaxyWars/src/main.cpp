#include "timerISR.h"
#include "helper.h"
#include "periph.h"
#include "spiAVR.h"
#include "SerialMonitor.h"
#include "Globals.h"
#include "Tasks.h"

Task gTasks[NUM_TASKS];

void TimerISR()
{
	for (uint32_t i = 0; i < NUM_TASKS; i++)
	{
		if (gTasks[i].m_elapsedTime == gTasks[i].m_period)
		{
			gTasks[i].m_state = gTasks[i].m_TickFunction(gTasks[i].m_state);
			gTasks[i].m_elapsedTime = 0;
		}

		gTasks[i].m_elapsedTime += PERIOD_GCD;
	}
}

void SetResetPin(bool newVal)
{
	PORTD = SetBit(PORTD, PORTD7, newVal);
}

void HardwareReset()
{
	SetResetPin(0);
	_delay_ms(200);
	SetResetPin(1);
	_delay_ms(200);
	_delay_ms(200);
}

void Send_Command(int8_t command)
{
	PORTB = SetBit(PORTB, 0, 0);
	SPI_SEND(command);
	_delay_ms(200);
}

void Send_Data(int8_t data)
{
	PORTB = SetBit(PORTB, 0, 1);
	SPI_SEND(data);
	_delay_ms(200);
}

void ST7735_init()
{
	HardwareReset();
	Send_Command(SWRESET);
	_delay_ms(500);
	Send_Command(SLPOUT);
	_delay_ms(200);
	Send_Command(IDMOFF);
	_delay_ms(500);
	Send_Command(COLMOD);
	Send_Data(6); // 18-bit pixel
	_delay_ms(200);
	Send_Command(DISPON);
	_delay_ms(200);
}

int main()
{
	// Initialize Pins
	// [0-7] PORTD (8bit)
	// [8-13] PORTB (6bit)
	// [A0-A5] PORTC (6bit)
	// Output: DDR=1, PORT=0
	// PINx: Read Input
	// PORTx: Set Output

	Serial_Init(9600);

	DDRD = 0xFF; PORTD = 0;
	DDRB = 0xFF; PORTB = 0;
	DDRC = 0xFF; PORTC = 0;

	SPI_INIT();
	ST7735_init();

	PORTB = SetBit(PORTB, PORTB1, 1); // Turn on LED

	// CASET: Set Column
	Send_Command(CASET);
	Send_Data(0); Send_Data(64);
	Send_Data(0); Send_Data(127);
	Serial_PrintLine("set col");

	_delay_ms(500);

	// RASET: Set Row
	Send_Command(RASET);
	Send_Data(0); Send_Data(64); // row min (high, low)
	Send_Data(0); Send_Data(127); // row max (high, low)
	Serial_PrintLine("set row");

	_delay_ms(500);

	// RAMWR: Write Data
	Send_Command(RAMWR);
	Send_Data(0x00);
	Send_Data(0xFF);
	Send_Data(0x00);

	Serial_PrintLine("set mem data");

	_delay_ms(500);

	gTasks[0] = {TS_RENDER_INIT, PERIOD_GCD, PERIOD_GCD, &Tick_Render};

	TimerSet(PERIOD_GCD); 
	TimerOn();

	while (1){}

	return 0;
}
