#pragma once

#define FORCE_INLINE __attribute__((always_inline)) inline

#define ArraySize(array) (sizeof(array) / sizeof(array[0]))

