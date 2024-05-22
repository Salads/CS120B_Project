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

	ST7735SClient client;
	client.Initialize();
	
	client.FillCurrentScreenRegion(0, 255, 0);

	client.SetRegion(32, 96, 32, 128);
	client.FillCurrentScreenRegion(255, 0, 0);

	client.SetRegion(44, 84, 44, 116);
	client.FillCurrentScreenRegion(0, 0, 255);

	client.SetRegion(56, 72, 56, 104);
	client.FillCurrentScreenRegion(255, 165, 0);


	gTasks[0] = {TS_RENDER_INIT, PERIOD_GCD, PERIOD_GCD, &Tick_Render};

	TimerSet(PERIOD_GCD); 
	TimerOn();

	while (1){}

	return 0;
}
