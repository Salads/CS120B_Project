#pragma once

#define FORCE_INLINE __attribute__((always_inline)) inline

#define ArraySize(array) (sizeof(array) / sizeof(array[0]))

#define K_MAX_ENEMIES 4
#define K_BULLET_SPEED 8
#define K_PLAYER_SPEED 15
#define K_ENEMY_SPEED  10
