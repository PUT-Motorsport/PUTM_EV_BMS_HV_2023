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
#include "stm32h5xx_hal.h"

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
#define ADC_NDRY_Pin GPIO_PIN_0
#define ADC_NDRY_GPIO_Port GPIOC
#define SPI_RDY_Pin GPIO_PIN_1
#define SPI_RDY_GPIO_Port GPIOC
#define NFLT_Pin GPIO_PIN_2
#define NFLT_GPIO_Port GPIOC
#define SIGNAL_AMS_ERROR_Pin GPIO_PIN_3
#define SIGNAL_AMS_ERROR_GPIO_Port GPIOC
#define ADC_NSS_Pin GPIO_PIN_4
#define ADC_NSS_GPIO_Port GPIOA
#define ADC_SCK_Pin GPIO_PIN_5
#define ADC_SCK_GPIO_Port GPIOA
#define ADC_MISO_Pin GPIO_PIN_6
#define ADC_MISO_GPIO_Port GPIOA
#define ADC_MOSI_Pin GPIO_PIN_7
#define ADC_MOSI_GPIO_Port GPIOA
#define COM_NSS_Pin GPIO_PIN_15
#define COM_NSS_GPIO_Port GPIOA
#define COM_SCK_Pin GPIO_PIN_10
#define COM_SCK_GPIO_Port GPIOC
#define COM_MISO_Pin GPIO_PIN_11
#define COM_MISO_GPIO_Port GPIOC
#define COM_MOSI_Pin GPIO_PIN_12
#define COM_MOSI_GPIO_Port GPIOC
#define LED_ERROR_Pin GPIO_PIN_2
#define LED_ERROR_GPIO_Port GPIOD
#define LED_WARNING_Pin GPIO_PIN_3
#define LED_WARNING_GPIO_Port GPIOB
#define LED_OK_Pin GPIO_PIN_4
#define LED_OK_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
