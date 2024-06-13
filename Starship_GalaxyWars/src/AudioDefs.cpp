#include "AudioDefs.h"
#include "Defines.h"
#include <avr/pgmspace.h>

const uint16_t gNoteFrequenices [] PROGMEM = 
{
	16,17,18,19,21,22,23,25,26,28,29,31,
	33,35,37,39,41,44,46,49,52,55,58,62,
	65,69,73,78,82,87,93,98,104,110,117,123,
	131,139,147,156,165,175,185,196,208,220,233,247,
	262,277,294,311,330,349,370,392,415,440,466,494,
	523,554,587,622,659,698,740,784,831,880,932,988,
	1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976,
	2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951,
	4186,4435,4699,4978,5274,5588,5920,6272,6645,7040,7459,7902, 
	0
};

const uint8_t song_sf_controls_bpm = 120;
const uint8_t song_sf_controls_data [] PROGMEM = 
{
	A4, NoteLen_Quarter, 
	Rest, NoteLen_Eighths,
	E5, NoteLen_Quarter, 
	Rest, NoteLen_Eighths,
	Rest, NoteLen_Half,

	D5S, NoteLen_Eighths,
	E5, NoteLen_Eighths,
	F5S, NoteLen_Eighths,
	B4, NoteLen_Eighths,
	C5S, NoteLen_Eighths,
	D5S, NoteLen_Eighths,

	F5S, NoteLen_Quarter,
	Rest, NoteLen_Eighths,

	E5, NoteLen_Sixteenths,
	D5S, NoteLen_Sixteenths,
	E5, NoteLen_Quarter,
	Rest, NoteLen_Half,
	
	E5, NoteLen_Quarter,
	F5S, NoteLen_Quarter,
	G5S, NoteLen_Quarter,
	A5, NoteLen_Quarter,

	Rest, NoteLen_Eighths,
	D5, NoteLen_Sixteenths,
	C5S, NoteLen_Sixteenths,
	D5, NoteLen_Quarter,

	A5, NoteLen_Quarter,
	A5, NoteLen_Quarter,
	Rest, NoteLen_Sixteenths,

	D5, NoteLen_Sixteenths,
	C5S, NoteLen_Sixteenths,
	D5, NoteLen_Quarter,

	A5, NoteLen_Quarter,
	B5, NoteLen_Quarter,
	Rest, NoteLen_Quarter,
	Rest, NoteLen_Quarter,
	Rest, NoteLen_Quarter,

	E5, NoteLen_Quarter,
	Rest, NoteLen_Quarter,
	Rest, NoteLen_Quarter,
};
const uint16_t song_sf_controls_datasize = ArraySize(song_sf_controls_data);

const uint8_t song_mq_battle2_bpm = 124;
const uint8_t song_mq_battle2_data [] PROGMEM = 
{
	// motif
	B4, NoteLen_Quarter,
	F5S, NoteLen_Quarter,
	E5, NoteLen_Sixteenths,
	F5S, NoteLen_Sixteenths,
	E5, NoteLen_Sixteenths,
	D5, NoteLen_Sixteenths,
	E5, NoteLen_Sixteenths,
	D5, NoteLen_Sixteenths,
	C5S, NoteLen_Sixteenths,
	A4, NoteLen_Sixteenths,
	G4, NoteLen_Eighths,
	D5, NoteLen_Sixteenths,
	C5S, NoteLen_Eighths,
	A4, NoteLen_Sixteenths,
	B4, NoteLen_Sixteenths,
	B4, NoteLen_Quarter,

	Rest, NoteLen_Quarter,

	// bridge p1
	B5, NoteLen_Eighths,
	F5S, NoteLen_Sixteenths,
	B5, NoteLen_Eighths,
	F5S, NoteLen_Sixteenths,
	F6S, NoteLen_Sixteenths,
	E6, NoteLen_Sixteenths,
	E6, NoteLen_Quarter,

	Rest, NoteLen_Quarter,

	//bridge p2
	B4, NoteLen_Eighths,
	B4, NoteLen_Sixteenths,
	F4S, NoteLen_Eighths,
	G4, NoteLen_Sixteenths,
	B4, NoteLen_Sixteenths,
	D5, NoteLen_Eighths,
	E5, NoteLen_Sixteenths,
	D5, NoteLen_Sixteenths,
	C5S, NoteLen_Quarter,

	// motif repeat
	B4, NoteLen_Quarter,
	F5S, NoteLen_Quarter,
	E5, NoteLen_Sixteenths,
	F5S, NoteLen_Sixteenths,
	E5, NoteLen_Sixteenths,
	D5, NoteLen_Sixteenths,
	E5, NoteLen_Sixteenths,
	D5, NoteLen_Sixteenths,
	C5S, NoteLen_Sixteenths,
	A4, NoteLen_Sixteenths,
	G4, NoteLen_Eighths,
	D5, NoteLen_Sixteenths,
	C5S, NoteLen_Eighths,
	A4, NoteLen_Sixteenths,
	B4, NoteLen_Sixteenths,
	B4, NoteLen_Quarter,

	Rest, NoteLen_Quarter,

	// end
	D6, NoteLen_Sixteenths,
	C6S, NoteLen_Sixteenths,
	A5, NoteLen_Sixteenths,
	B5, NoteLen_Sixteenths,
	F5S, NoteLen_Sixteenths,
	B4, NoteLen_Sixteenths,
	D5, NoteLen_Sixteenths,
	B5, NoteLen_Sixteenths,

	A5, NoteLen_Sixteenths,
	A5, NoteLen_Eighths,

	E5, NoteLen_Sixteenths,
	E5, NoteLen_Eighths,

	C5S, NoteLen_Eighths,
	C6S, NoteLen_Eighths,
	D6, NoteLen_Sixteenths,

	B5, NoteLen_Quarter,
	B5, NoteLen_Quarter,
	B5, NoteLen_Quarter,
	B5, NoteLen_Sixteenths,
};
const uint16_t song_mq_battle2_datasize = ArraySize(song_mq_battle2_data);
