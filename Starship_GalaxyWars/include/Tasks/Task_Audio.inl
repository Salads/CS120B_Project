#include "Tasks.h"
#include "AudioDefs.h"
#include "AudioPlayer.h"

int Tick_Audio(int state)
{
	switch(state)
	{
		case TS_AUDIO_WAIT: state = TS_AUDIO_PLAY; break;
		case TS_AUDIO_PLAY: break;
	}

	switch(state)
	{
		case TS_AUDIO_WAIT: break;
		case TS_AUDIO_PLAY:
			gAudioPlayer.Update();
		break;
	}

	return state;
}
