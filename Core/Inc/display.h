#pragma once
#include <stdint.h>

void drawSplashScreen(void);
void drawStartupScreen(uint8_t mode);
void drawSensorBarInline();
void drawMeasurement(uint32_t baseline, uint32_t new, uint32_t latency);
void drawAverage(float mean_ms, float sd_ms);
void drawMainMenuInline(uint8_t index);
void drawParamsMenu(uint8_t index);
void drawError(char * error);