#include "usb.h"
#include "main.h"
#include <stdint.h>
#include <stdlib.h>

#include "display.h"
#include "hid_device.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "usb_descriptors.h"
#include "usbd.h"

/**
 * @brief Triggers a mouse action based on the current menu index. Needs TIM2 to
 * be reset & started.
 * @details To be used as the first action within a latency measurement.
 * Depending on `mainMenuIndex`, either clicks mouse1 or moves by 127px x, 127px
 * y. It waits for the USB HID interface to be ready. If a timeout occurs (6
 * seconds), it triggers an error state by flashing the error LED and displaying
 * a message.
 * @return int8_t Error code
 */
int8_t start_mouse_action() {
  HAL_GPIO_WritePin(INF_LED_GPIO_Port, INF_LED_Pin, GPIO_PIN_SET);

  while (!tud_hid_ready()) {
    tud_task();
    if (TIM2->CNT > 6000000) {
      HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET);
      draw_error_overlay("USB timeout", "Check USB", "connection");
      HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET);
      return 1;
    }
  }

  tud_hid_mouse_report(REPORT_ID_MOUSE, latency_mode_selector == CLICK,
                       latency_mode_selector == MOVE ? 127 : 0,
                       latency_mode_selector == MOVE ? 127 : 0, 0, 0);
  return 0;
}

/**
 * @brief Generates a random mouse move wheel scroll report and sends it via USB HID.
 *
 * @details The mouse report contains a random x/y move of -3 to 3 pixels 
 * and vertical wheel delta of -1 to 3. The function waits for the USB HID 
 * interface to become ready. If a timeout occurs (6 seconds), it triggers an error 
 * state by turning on the error LED, displaying a message, and delaying before returning. Upon
 * successful transmission, it flashes the info LED to indicate completion.
 */
void random_mouse_move() {
  HAL_TIM_Base_Stop_IT(&htim2);
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  HAL_TIM_Base_Start_IT(&htim2);

  while (!tud_hid_ready()) {
    tud_task();
    if (TIM2->CNT > 6000000) {
      HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET);
      draw_error_overlay("USB timeout", "Check USB", "connection");
      HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET);
      return;
    }
  }

  tud_hid_mouse_report(REPORT_ID_MOUSE, 0, rand() % 7 - 3, rand() % 7 - 3,
    rand() % 7 - 3, 0);

  HAL_GPIO_WritePin(INF_LED_GPIO_Port, INF_LED_Pin, GPIO_PIN_SET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(INF_LED_GPIO_Port, INF_LED_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Resets mouse state by sending HID input.
 *
 * @details To be used after measurement with @ref startMouseAction is finished.
 * Depending on `mainMenuIndex`, sets `buttons` to 0 for a releasing or `x` and
 * `y` to -127 for a move back to the original position. It waits for the USB
 * HID interface to be ready. If a timeout occurs (6 seconds), it triggers an
 * error state by flashing the error LED and displaying a message. Finally, it
 * sends the report.
 * @return int8_t Error code
 */
int8_t stop_mouse_action() {
  HAL_TIM_Base_Stop_IT(&htim2);
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  HAL_TIM_Base_Start_IT(&htim2);
  while (!tud_hid_ready()) {
    tud_task();
    if (TIM2->CNT > 6000000) {
      HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET);
      draw_error_overlay("USB timeout", "Check USB", "connection");
      HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET);
      return 1;
    }
  }

  HAL_GPIO_WritePin(INF_LED_GPIO_Port, INF_LED_Pin, GPIO_PIN_RESET);
  tud_hid_mouse_report(REPORT_ID_MOUSE, 0, latency_mode_selector == MOVE ? -127 : 0,
                       latency_mode_selector == MOVE ? -127 : 0, 0, 0);

  return 0;
}