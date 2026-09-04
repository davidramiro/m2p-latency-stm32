#include "sleep.h"
#include "main.h"

volatile uint8_t led_interrupt_counter = 0;
volatile uint16_t standby_interrupt_counter = 0;
volatile uint8_t sleep_requested = 0;
volatile uint8_t wakeup_requested = 0;
volatile uint8_t display_sleeping = 0;

/**
 * @brief Enters low-power sleep mode if the sleep request flag is set.
 * @details Stops hardware timers and suspends the system tick before entering
 * SLEEP mode. Restores timers, resumes the system tick, and powers the display
 * upon waking.
 */
void handle_MCU_sleep() {
  if (sleep_requested) {
    sleep_requested = 0;
    u8g2_SetPowerSave(&u8g2, 1);

    display_sleeping = 1;

    HAL_TIM_Base_Stop_IT(&htim3);
    HAL_TIM_Base_Stop_IT(&htim4);
    HAL_SuspendTick();

    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);

    HAL_ResumeTick();
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);

    u8g2_SetPowerSave(&u8g2, 0);
    display_sleeping = 0;
    wakeup_requested = 0;
  }
}

/**
 * @brief Manages display sleep state and pulses INF led when sleeping.
 * @details Checks the display_sleeping flag to determine the current state.
 * If a sleep request is detected, the U8G2 display is powered down. If a
 * wake-up request is detected, the display is powered back up and request
 * flags are cleared after processing.
 */
void handle_display_sleep() {
  if (sleep_requested) {
    if (!display_sleeping) {
      u8g2_SetPowerSave(&u8g2, 1);
      display_sleeping = 1;
    }
    sleep_requested = 0;
  }
  if (wakeup_requested) {
    if (display_sleeping) {
      u8g2_SetPowerSave(&u8g2, 0);
      display_sleeping = 0;
    }
  }
  wakeup_requested = 0;
}
