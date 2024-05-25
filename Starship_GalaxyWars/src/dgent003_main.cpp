#include "timerISR.h"
#include "periph.h"
#include "SPIUtil.h"
#include "SerialMonitor.h"
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
	// Output: DDRx=1, PORTx=0
	// PINx: Read Input
	// PORTx: Set Output

	Serial_Init(9600);

	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFF; PORTB = 0;
	DDRC = 0xFF; PORTC = 0;

#if false
	while(1)
	{
		Serial_PrintLine((PIND >> 7) & 0x01);
		_delay_ms(50);
	}
#endif

	SPI_INIT();

	gTasks[0] = {TS_RENDER_INIT, PERIOD_GCD, PERIOD_GCD, &Tick_Render};

	TimerSet(PERIOD_GCD); 
	TimerOn();

	while (1){}

	return 0;
}
