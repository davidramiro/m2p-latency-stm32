#pragma once
#include <stdint.h>

void drawSplashScreen(void);
void drawStartupScreen(uint32_t min, uint32_t max, uint32_t cur, uint8_t mode);
void drawSensorBarInline(uint32_t min, uint32_t max, uint32_t cur);
void drawMeasurement(uint32_t baseline, uint32_t new, uint32_t latency);
void printAverage(float mean_ms, float sd_ms);
void drawMenuInline(uint8_t index);