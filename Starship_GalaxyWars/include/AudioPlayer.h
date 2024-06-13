#pragma once

#include <stdint.h>
#include "AudioDefs.h"

enum AudioPlayerMode : uint8_t
{
	AudioPlayerMode_Single,
	AudioPlayerMode_Repeat
};

// Plays notes on the passive buzzer
class AudioPlayer
{
public:
	void LoadSong(const uint8_t* data, uint16_t dataSize, uint8_t bpm, AudioPlayerMode mode = AudioPlayerMode_Single);
	void Stop();
	void Update();
	bool IsPlaying();
private:
	uint8_t* m_data;
	uint16_t m_dataSize;
	uint8_t  m_bpm = 0;
	uint16_t m_noteLengthsMS[5];
	uint32_t m_time = 0; // Records time played on current note via ticks. Might be unreliable due to this.

	uint16_t m_dataIdx = 0;
	AudioPlayerMode m_mode;
};

extern AudioPlayer gAudioPlayer;
