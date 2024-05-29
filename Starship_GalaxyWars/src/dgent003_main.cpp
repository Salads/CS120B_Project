#include "TimerISR.h"
#include "Periph.h"
#include "SPIUtil.h"
#include "SerialMonitor.h"
#include "Tasks/Tasks.h"

Task gTasks[NUM_TASKS];

void TimerISR()
{
	GameState::Get().m_currentTimeMS++;
	for (uint8_t i = 0; i < NUM_TASKS; i++)
	{
		if (gTasks[i].m_elapsedTime >= gTasks[i].m_period)
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
	DDRC = 0x00; PORTC = 0xFF;

	SPI_INIT();
	InitializeADC();

	gTasks[0] = {TS_BUTTONS_INIT , PERIOD_BUTTONS , PERIOD_BUTTONS , &Tick_Buttons};
	gTasks[1] = {TS_JOYSTICK_INIT, PERIOD_JOYSTICK, PERIOD_JOYSTICK, &Tick_Joystick};
	gTasks[2] = {TS_UPDATE_INIT  , PERIOD_UPDATE  , PERIOD_UPDATE  , &Tick_Update};
	gTasks[3] = {TS_RENDER_INIT  , PERIOD_RENDER  , PERIOD_RENDER  , &Tick_Render};

	gTasks[NUM_TASKS - 1] = {TS_TIMING_INIT, PERIOD_TIMING, PERIOD_TIMING, &Tick_Timing};

	TimerSet(PERIOD_GCD); 
	TimerOn();

	while (1){}

	return 0;
}
