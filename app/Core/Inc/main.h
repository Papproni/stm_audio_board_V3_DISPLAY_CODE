/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define LED_OK_Pin GPIO_PIN_14
#define LED_OK_GPIO_Port GPIOC
#define ILI9341_CS_Pin GPIO_PIN_6
#define ILI9341_CS_GPIO_Port GPIOF
#define T_CS_Pin GPIO_PIN_4
#define T_CS_GPIO_Port GPIOA
#define POT1_Pin GPIO_PIN_6
#define POT1_GPIO_Port GPIOA
#define POT2_Pin GPIO_PIN_7
#define POT2_GPIO_Port GPIOA
#define POT4_Pin GPIO_PIN_4
#define POT4_GPIO_Port GPIOC
#define POT3_Pin GPIO_PIN_1
#define POT3_GPIO_Port GPIOB
#define POT5_Pin GPIO_PIN_11
#define POT5_GPIO_Port GPIOF
#define POT6_Pin GPIO_PIN_12
#define POT6_GPIO_Port GPIOF
#define T_IRQ_Pin GPIO_PIN_6
#define T_IRQ_GPIO_Port GPIOD
#define ILI9341_RESET_Pin GPIO_PIN_10
#define ILI9341_RESET_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
