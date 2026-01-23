#include <stdint.h>
#include <stdlib.h>

#include "../Inc/main.h"
#include "../Inc/display.h"
#include "../Inc/measure.h"

#include <math.h>

#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"

uint32_t readADC() {
    uint32_t adc_val = 0;
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_TIMEOUT) {
        adc_val = HAL_ADC_GetValue(&hadc1);
    }
    HAL_ADC_Stop(&hadc1);

    return adc_val;
}

uint32_t readAveragedADC() {
    uint32_t adc_val = 0;
    for (int i = 0; i < NUM_CYCLES; i++) {
        adc_val += readADC();
    }
    return adc_val / NUM_CYCLES;
}

void measure(void) {
    const uint32_t baseline = readADC();

    drawMeasurement(baseline, -1, -1);

    const uint32_t start = startMouseAction();

    while (1) {
        const int32_t delta = readADC() - baseline;

        if (abs(delta) > 50) {
            uint32_t latency = (uint32_t)__HAL_TIM_GET_COUNTER(&htim2) - start;
            stopMouseAction();

            if (cycle_index < NUM_CYCLES) {
                latencies_us[cycle_index] = latency;
            }

            drawMeasurement(baseline, baseline + delta, latency);

            HAL_Delay(MEASUREMENT_DELAY);

            break;
        }
    }
}

void computeStatsMs(float *mean_ms, float *sd_ms) {
    float sum_us = 0.0f;
    float variance_us = 0.0f;

    if (NUM_CYCLES == 1) {
        *mean_ms = latencies_us[0] / MS_FACTOR;
        *sd_ms = 0.0f;
        return;
    }

    // calculate mean
    for (int i = 0; i < NUM_CYCLES; i++) {
        sum_us += (float)latencies_us[i];
    }
    const float mean_us = sum_us / (float) NUM_CYCLES;

    // calculate sample standard deviation
    for (int i = 0; i < NUM_CYCLES; i++) {
        const float diff_us = (float)latencies_us[i] - mean_us;
        variance_us += diff_us * diff_us;
    }
    const float sd_us = sqrtf(variance_us / (NUM_CYCLES - 1));

    *mean_ms = mean_us / MS_FACTOR;
    *sd_ms = sd_us / MS_FACTOR;
}
