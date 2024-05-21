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

	SPI_INIT();

	gTasks[0] = {TS_RENDER_INIT, PERIOD_GCD, PERIOD_GCD, &Tick_Render};

	TimerSet(PERIOD_GCD);
	TimerOn();

	while (1){}

	return 0;
}
