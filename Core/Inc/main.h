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

uint32_t startMouseAction();

void stopMouseAction();

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_UP_Pin GPIO_PIN_8
#define BTN_UP_GPIO_Port GPIOA
#define BTN_DN_Pin GPIO_PIN_9
#define BTN_DN_GPIO_Port GPIOA
#define BTN_CNT_Pin GPIO_PIN_10
#define BTN_CNT_GPIO_Port GPIOA
#define BTN_LFT_Pin GPIO_PIN_3
#define BTN_LFT_GPIO_Port GPIOB
#define BTN_RGT_Pin GPIO_PIN_4
#define BTN_RGT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define HID_REPORT_SIZE 4
#define BTN_DEBOUNCE_DELAY 60
#define DEFAULT_THRESHOLD 40
#define DEFAULT_NUM_CYCLES 10

extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;
extern uint16_t cycle_index;
extern uint8_t num_cycles;
extern uint16_t sensor_threshold;

extern uint32_t min_adc_val;
extern uint32_t max_adc_val;
extern uint32_t cur_adc_val;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
