#pragma once
#include <stdint.h>

#define MS_FACTOR 1000.0f
#define MEASUREMENT_DELAY 503

uint32_t readADC();
uint32_t readAveragedADC();
void measure(uint32_t latencies_us[]);
void computeStatsMs(uint32_t latencies_us[], float *mean_ms, float *sd_ms);