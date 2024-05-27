#pragma once

#include "Task.h"
#include "ST7735SClient.h"

#define NUM_TASKS 4
#define PERIOD_GCD 1
#define PERIOD_RENDER   200
#define PERIOD_UPDATE   200
#define PERIOD_BUTTONS  1
#define PERIOD_JOYSTICK 1
#define PERIOD_TIMING   1

enum TS_Joystick : uint8_t {TS_JOYSTICK_INIT, TS_JOYSTICK_SAMPLE};
enum TS_Buttons  : uint8_t {TS_BUTTONS_INIT,  TS_BUTTONS_SAMPLE };
enum TS_Update 	 : uint8_t {TS_UPDATE_INIT,   TS_UPDATE_DOUPDATE};
enum TS_Audio    : uint8_t {TS_AUDIO_INIT,    TS_AUDIO_DOAUDIO  };
enum TS_Render   : uint8_t {TS_RENDER_INIT,   TS_RENDER_DORENDER};
enum TS_Timing   : uint8_t {TS_TIMING_INIT,   TS_TIMING_UPDATE  };

FORCE_INLINE int Tick_Joystick(int state);
FORCE_INLINE int Tick_Buttons(int state);
FORCE_INLINE int Tick_Update(int state);
FORCE_INLINE int Tick_Audio(int state);
FORCE_INLINE int Tick_Render(int state);
FORCE_INLINE int Tick_Timing(int state); // Just updates the last frame time. ALWAYS keep this as the last task!


#include "Tasks.inl"
