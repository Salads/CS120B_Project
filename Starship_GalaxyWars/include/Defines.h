#pragma once

#include "Utility.h"

#define FORCE_INLINE __attribute__((always_inline)) inline
#define ArraySize(array) (sizeof(array) / sizeof(array[0]))
#define SecondsToMS(seconds) (seconds*1000)

#define TIMER2_VAL   250
#define K_PLAYER_BULLET_FIREINTERVAL SecondsToMS(0.0025)

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

#define K_MAX_ENEMIES 2
#define K_BULLET_SPEED 3
#define K_PLAYER_SPEED 15
#define K_ENEMY_SPEED  10
#define K_MAX_BULLETS  10