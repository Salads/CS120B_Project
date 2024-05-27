#pragma once

#include <stdint.h>

////////// ADC UTILITY FUNCTIONS ///////////

void InitializeADC();
uint32_t ReadADC(uint8_t channel);
