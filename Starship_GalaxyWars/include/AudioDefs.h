#pragma once

#include "stdint.h"

// Index value, actual frequencies are in an array 
enum Note : uint8_t
{
	C0,C0S,D0,D0S,E0,F0,F0S,G0,G0S,A0,A0S,B0,
	C1,C1S,D1,D1S,E1,F1,F1S,G1,G1S,A1,A1S,B1,
	C2,C2S,D2,D2S,E2,F2,F2S,G2,G2S,A2,A2S,B2,
	C3,C3S,D3,D3S,E3,F3,F3S,G3,G3S,A3,A3S,B3,
	C4,C4S,D4,D4S,E4,F4,F4S,G4,G4S,A4,A4S,B4,
	C5,C5S,D5,D5S,E5,F5,F5S,G5,G5S,A5,A5S,B5,
	C6,C6S,D6,D6S,E6,F6,F6S,G6,G6S,A6,A6S,B6,
	C7,C7S,D7,D7S,E7,F7,F7S,G7,G7S,A7,A7S,B7,
	C8,C8S,D8,D8S,E8,F8,F8S,G8,G8S,A8,A8S,B8,
	Rest
};

extern const uint16_t gNoteFrequenices[];

enum NoteLen : uint8_t
{
	NoteLen_Whole,
	NoteLen_Half,
	NoteLen_Quarter,
	NoteLen_Eighths,
	NoteLen_Sixteenths
};

extern const uint8_t song_sf_controls_bpm;
extern const uint8_t song_sf_controls_data [];
extern const uint16_t song_sf_controls_datasize;

extern const uint8_t song_mq_battle2_bpm;
extern const uint8_t song_mq_battle2_data [];
extern const uint16_t song_mq_battle2_datasize;
