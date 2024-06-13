#include "AudioPlayer.h"
#include "SerialMonitor.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "GameState.h"

void AudioPlayer::LoadSong(const uint8_t* data, uint16_t dataSize, uint8_t bpm, AudioPlayerMode mode)
{
	// Set song parameters
	m_data 	   = (uint8_t*)data;
	m_dataSize = dataSize;
	m_bpm 	   = bpm;
	m_dataIdx  = 0;

	m_mode = mode;

	// Calculate how long in ms notes take.
	uint16_t quarterNoteLengthMS = (60000 / m_bpm); // MS per minute / beats per minute -> minutes cancel out -> MS per Beat (quarter note)

	m_noteLengthsMS[NoteLen_Whole] 		= quarterNoteLengthMS * 4;
	m_noteLengthsMS[NoteLen_Half] 		= quarterNoteLengthMS * 2;
	m_noteLengthsMS[NoteLen_Quarter] 	= quarterNoteLengthMS * 1;
	m_noteLengthsMS[NoteLen_Eighths] 	= quarterNoteLengthMS / 2;
	m_noteLengthsMS[NoteLen_Sixteenths] = quarterNoteLengthMS / 4;
}

void AudioPlayer::Stop()
{
	OCR1A = 0;
	m_data = 0;
	m_dataSize = 0;
	m_dataIdx = 0;
	m_bpm = 0;
	m_time = 0;
}

void AudioPlayer::Update()
{
	if(!m_data) {return;}
	if(m_dataIdx >= m_dataSize) 
	{
		if(m_mode == AudioPlayerMode_Single) {OCR1A = 0; return;}
		else if(m_mode == AudioPlayerMode_Repeat)
		{
			m_dataIdx = 0;
			m_time = 0;
		}
	}

	// Data format is uint8 for the note, uint8 for duration
	uint8_t note = pgm_read_byte(m_data + m_dataIdx);
	uint8_t dur = pgm_read_byte(m_data + m_dataIdx + 1);

	//Debug_PrintLine("Note: %d, Dur: %d", note, dur);
	uint16_t currentNote 			= pgm_read_word(gNoteFrequenices + note);
	uint16_t currentNoteDuration 	= m_noteLengthsMS[dur];

	if(++m_time < currentNoteDuration)
	{
		// Make sure we set frequency or turn off timer if rest
		if(currentNote == 0)
		{
			OCR1A = 0;
		}
		else
		{
			OCR1A = (16000000 / (2 * currentNote)) - 1;
		}
	}
	else // time passed, advance data idx
	{
		m_dataIdx += 2;
		m_time = 0;
	}
}

bool AudioPlayer::IsPlaying()
{
	bool isPlaying = false;
	if(!m_data) 
	{
		isPlaying = false;
	}
	else if(m_dataIdx >= m_dataSize) 
	{
		isPlaying = m_mode == AudioPlayerMode_Repeat;
	}
	else
	{
		isPlaying = true;
	}

	return isPlaying;
}

AudioPlayer gAudioPlayer;
