#pragma once

struct Task
{
	unsigned char m_state; 			//Task's current state
	unsigned long m_period; 		//Task period
	unsigned long m_elapsedTime; 	//Time elapsed since last task tick
	int (*m_TickFunction)(int); 	//Task tick function
};
