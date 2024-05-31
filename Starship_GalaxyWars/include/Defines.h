#pragma once

#include "Utility.h"

#define FORCE_INLINE __attribute__((always_inline)) inline
#define ArraySize(array) (sizeof(array) / sizeof(array[0]))
#define SecondsToMS(seconds) (seconds*1000)

#define K_PLAYER_BULLET_FIREINTERVAL 200

// Weird screen size, but I incremented 1by1 on each dimension till the screen filled. /shrug
#define SCREEN_WIDTH 130
#define SCREEN_HEIGHT 131
#define TOP_HUD_HEIGHT    10 // Reserve some space for HUD
#define BOTTOM_HUD_HEIGHT 10 // Reserve some space for HUD

#define K_BULLET_SPEED 1
#define K_PLAYER_SPEED 1
#define K_ENEMY_SPEED  1
#define K_MAX_BULLETS  15