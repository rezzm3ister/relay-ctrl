/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "appl_main.h"
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
#define Relay1_Pin GPIO_PIN_0
#define Relay1_GPIO_Port GPIOB
#define Relay2_Pin GPIO_PIN_1
#define Relay2_GPIO_Port GPIOB
#define LED_Mains_Pin GPIO_PIN_12
#define LED_Mains_GPIO_Port GPIOB
#define LED_Solar_Pin GPIO_PIN_13
#define LED_Solar_GPIO_Port GPIOB
#define LED_Override_Pin GPIO_PIN_14
#define LED_Override_GPIO_Port GPIOB
#define Relay3_Pin GPIO_PIN_3
#define Relay3_GPIO_Port GPIOB
#define Relay4_Pin GPIO_PIN_4
#define Relay4_GPIO_Port GPIOB
#define Override_EN_Pin GPIO_PIN_5
#define Override_EN_GPIO_Port GPIOB
#define Override_Sel_Pin GPIO_PIN_8
#define Override_Sel_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
