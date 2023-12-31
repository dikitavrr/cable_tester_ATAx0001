/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_RESP_RED_SR_DATA_Pin GPIO_PIN_2
#define LED_RESP_RED_SR_DATA_GPIO_Port GPIOA
#define LED_RESP_GREEN_SR_DATA_Pin GPIO_PIN_3
#define LED_RESP_GREEN_SR_DATA_GPIO_Port GPIOA
#define LED_CALL_RED_SR_DATA_Pin GPIO_PIN_4
#define LED_CALL_RED_SR_DATA_GPIO_Port GPIOA
#define LED_CALL_GREEN_SR_DATA_Pin GPIO_PIN_5
#define LED_CALL_GREEN_SR_DATA_GPIO_Port GPIOA
#define STP_SR_LED_nCLR_Pin GPIO_PIN_6
#define STP_SR_LED_nCLR_GPIO_Port GPIOA
#define STP_SR_LED_CLK_Pin GPIO_PIN_7
#define STP_SR_LED_CLK_GPIO_Port GPIOA
#define Temp_sensor_cable_RED_LED_Pin GPIO_PIN_1
#define Temp_sensor_cable_RED_LED_GPIO_Port GPIOB
#define LINE_RESPONSE_SR_SHnLD_Pin GPIO_PIN_15
#define LINE_RESPONSE_SR_SHnLD_GPIO_Port GPIOA
#define LINE_RESPONSE_SR_CLK_Pin GPIO_PIN_3
#define LINE_RESPONSE_SR_CLK_GPIO_Port GPIOB
#define LINE_RESPONSE_SR_DATA_Pin GPIO_PIN_4
#define LINE_RESPONSE_SR_DATA_GPIO_Port GPIOB
#define LINE_CALL_SR_nCLR_Pin GPIO_PIN_5
#define LINE_CALL_SR_nCLR_GPIO_Port GPIOB
#define LINE_CALL_SR_CLK_Pin GPIO_PIN_6
#define LINE_CALL_SR_CLK_GPIO_Port GPIOB
#define LINE_CALL_SR_DATA_Pin GPIO_PIN_7
#define LINE_CALL_SR_DATA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
