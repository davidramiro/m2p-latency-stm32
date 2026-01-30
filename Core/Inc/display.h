#pragma once
#include <stdint.h>

void drawSplashScreen(void);
void drawStartupScreen(uint8_t mode);
void drawSensorBarInline();
void drawMeasurement(uint32_t baseline, uint32_t new, uint32_t latency);
void drawAverage(uint32_t latencies_us[], float mean_ms, float sd_ms);
void drawMainMenuInline(uint8_t index);
void drawParamsMenu(uint8_t index);
void drawError(char * error);
void drawGraphInline(uint32_t latencies_us[]);
uint32_t getMax(uint32_t latencies_us[]);
uint32_t getMin(uint32_t latencies_us[]);