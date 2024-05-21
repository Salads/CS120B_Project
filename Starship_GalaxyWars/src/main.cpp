#include "timerISR.h"
#include "helper.h"
#include "periph.h"
#include "SerialMonitor.h"
#include "Globals.h"

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
	TimerSet(PERIOD_GCD);
	TimerOn();

	while (1)
	{
	}

	return 0;
}
