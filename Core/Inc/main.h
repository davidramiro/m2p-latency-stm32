/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "u8g2.h"
#include "u8x8.h"
#include <stdint.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg,
                                         uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg,
                                      uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_byte_stm32_hw_i2c(u8x8_t *u8x8, uint8_t msg,
                                      uint8_t arg_int, void *arg_ptr);

void update_ADC_channel();

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IT_DEBOUNCE_US 20000
#define INT_SENSOR_Pin GPIO_PIN_1
#define INT_SENSOR_GPIO_Port GPIOA
#define EXT_SENSOR_Pin GPIO_PIN_4
#define EXT_SENSOR_GPIO_Port GPIOA
#define EXT_TRIGGER_Pin GPIO_PIN_5
#define EXT_TRIGGER_GPIO_Port GPIOA
#define BTN_LEFT_Pin GPIO_PIN_6
#define BTN_LEFT_GPIO_Port GPIOA
#define BTN_LEFT_EXTI_IRQn EXTI9_5_IRQn
#define BTN_CENTER_Pin GPIO_PIN_7
#define BTN_CENTER_GPIO_Port GPIOA
#define BTN_CENTER_EXTI_IRQn EXTI9_5_IRQn
#define BTN_DOWN_Pin GPIO_PIN_4
#define BTN_DOWN_GPIO_Port GPIOC
#define BTN_DOWN_EXTI_IRQn EXTI4_IRQn
#define BTN_RIGHT_Pin GPIO_PIN_5
#define BTN_RIGHT_GPIO_Port GPIOC
#define BTN_RIGHT_EXTI_IRQn EXTI9_5_IRQn
#define BTN_UP_Pin GPIO_PIN_0
#define BTN_UP_GPIO_Port GPIOB
#define BTN_UP_EXTI_IRQn EXTI0_IRQn
#define ERR_LED_Pin GPIO_PIN_11
#define ERR_LED_GPIO_Port GPIOC
#define INF_LED_Pin GPIO_PIN_12
#define INF_LED_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */
#define DEFAULT_THRESHOLD 40
#define DEFAULT_NUM_CYCLES 10
#define DEFAULT_ADC_CHANNEL 1
#define DISPLAY_SLEEP_TIMEOUT_S 60
#define JIGGLE_INTERVAL_MIN_S 1
#define JIGGLE_INTERVAL_MAX_S 15
#define ADDITIONAL_DEBOUNCE_MS 50

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern uint16_t cycle_index;
extern uint8_t num_cycles;
extern uint16_t sensor_threshold;
extern uint8_t adc_channel;
extern uint32_t min_adc_val;
extern uint32_t max_adc_val;
extern uint32_t cur_adc_val;

extern u8g2_t u8g2;

extern volatile uint8_t btn_up_pressed;
extern volatile uint8_t btn_down_pressed;
extern volatile uint8_t btn_left_pressed;
extern volatile uint8_t btn_right_pressed;
extern volatile uint8_t btn_center_pressed;

extern volatile uint16_t standby_interrupt_counter;
extern volatile uint8_t led_interrupt_counter;
extern volatile uint8_t sleep_requested;
extern volatile uint8_t wakeup_requested;
extern volatile uint8_t display_sleeping;

typedef enum { CYCLES = 0, THRESHOLD = 1, SENSOR = 2, EXIT = 3 } MainMenu;
typedef enum { LATENCY = 0, JIGGLER = 1, PARAMS = 2 } ParamsMenu;
typedef enum { CLICK = 0, MOVE = 1, EXTERNAL = 2 } LatencyMode;

extern ParamsMenu main_menu_selector;
extern LatencyMode latency_mode_selector;
extern MainMenu params_menu_selector;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
