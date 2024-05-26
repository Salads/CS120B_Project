#pragma once

#include "Task.h"
#include "ST7735SClient.h"

#define NUM_TASKS 1
#define PERIOD_GCD 1000

enum TS_Joystick : uint8_t {TS_JOYSTICK_INIT, TS_JOYSTICK_SAMPLE};
enum TS_Buttons  : uint8_t {TS_BUTTONS_INIT,  TS_BUTTONS_SAMPLE };
enum TS_Update 	 : uint8_t {TS_UPDATE_INIT,   TS_UPDATE_DOUPDATE};
enum TS_Audio    : uint8_t {TS_AUDIO_INIT,    TS_AUDIO_DOAUDIO  };
enum TS_Render   : uint8_t {TS_RENDER_INIT,   TS_RENDER_DORENDER};

FORCE_INLINE int Tick_Joystick(int state);
FORCE_INLINE int Tick_Buttons(int state);
FORCE_INLINE int Tick_Update(int state);
FORCE_INLINE int Tick_Audio(int state);
FORCE_INLINE int Tick_Render(int state);


#include "Tasks.inl"
