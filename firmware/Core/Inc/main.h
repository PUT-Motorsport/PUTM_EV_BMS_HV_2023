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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os2.h"
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
#define PUTM_USE_CAN_FD
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SAFETY_DETECT_Pin GPIO_PIN_13
#define SAFETY_DETECT_GPIO_Port GPIOC
#define FAN_CTRL7_Pin GPIO_PIN_0
#define FAN_CTRL7_GPIO_Port GPIOC
#define FAN_CTRL6_Pin GPIO_PIN_1
#define FAN_CTRL6_GPIO_Port GPIOC
#define FAN_CTRL5_Pin GPIO_PIN_2
#define FAN_CTRL5_GPIO_Port GPIOC
#define FAN_CTRL4_Pin GPIO_PIN_3
#define FAN_CTRL4_GPIO_Port GPIOC
#define FAN_CTRL3_Pin GPIO_PIN_0
#define FAN_CTRL3_GPIO_Port GPIOA
#define FAN_CTRL2_Pin GPIO_PIN_1
#define FAN_CTRL2_GPIO_Port GPIOA
#define FAN_CTRL1_Pin GPIO_PIN_2
#define FAN_CTRL1_GPIO_Port GPIOA
#define AIR_PRE_DETECT_Pin GPIO_PIN_3
#define AIR_PRE_DETECT_GPIO_Port GPIOA
#define CARD_DETECT_Pin GPIO_PIN_4
#define CARD_DETECT_GPIO_Port GPIOA
#define CARD_SCK_Pin GPIO_PIN_5
#define CARD_SCK_GPIO_Port GPIOA
#define CARD_MISO_Pin GPIO_PIN_6
#define CARD_MISO_GPIO_Port GPIOA
#define CARD_MOSI_Pin GPIO_PIN_7
#define CARD_MOSI_GPIO_Port GPIOA
#define NCARD_CS_Pin GPIO_PIN_4
#define NCARD_CS_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_0
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_1
#define LED3_GPIO_Port GPIOB
#define AIR_M_DETECT_Pin GPIO_PIN_2
#define AIR_M_DETECT_GPIO_Port GPIOB
#define AIR_P_DETECT_Pin GPIO_PIN_10
#define AIR_P_DETECT_GPIO_Port GPIOB
#define NLTC2_CS_Pin GPIO_PIN_11
#define NLTC2_CS_GPIO_Port GPIOB
#define NLTC1_CS_Pin GPIO_PIN_12
#define NLTC1_CS_GPIO_Port GPIOB
#define LTC_SCK_Pin GPIO_PIN_13
#define LTC_SCK_GPIO_Port GPIOB
#define LTC_MISO_Pin GPIO_PIN_14
#define LTC_MISO_GPIO_Port GPIOB
#define LTC_MOSI_Pin GPIO_PIN_15
#define LTC_MOSI_GPIO_Port GPIOB
#define SIG_AIR_PRE_Pin GPIO_PIN_7
#define SIG_AIR_PRE_GPIO_Port GPIOC
#define SIG_AIR_P_Pin GPIO_PIN_8
#define SIG_AIR_P_GPIO_Port GPIOC
#define SIG_AIR_M_Pin GPIO_PIN_9
#define SIG_AIR_M_GPIO_Port GPIOC
#define NMES_ISENS_CS_Pin GPIO_PIN_8
#define NMES_ISENS_CS_GPIO_Port GPIOA
#define NMES_EXT_V_CS_Pin GPIO_PIN_9
#define NMES_EXT_V_CS_GPIO_Port GPIOA
#define NMES_EXT_I_CS_Pin GPIO_PIN_10
#define NMES_EXT_I_CS_GPIO_Port GPIOA
#define AMS_FAULT_Pin GPIO_PIN_15
#define AMS_FAULT_GPIO_Port GPIOA
#define MES_SCK_Pin GPIO_PIN_10
#define MES_SCK_GPIO_Port GPIOC
#define MES_MISO_Pin GPIO_PIN_11
#define MES_MISO_GPIO_Port GPIOC
#define MES_MOSI_Pin GPIO_PIN_12
#define MES_MOSI_GPIO_Port GPIOC
#define NMES_CAR_CS_Pin GPIO_PIN_2
#define NMES_CAR_CS_GPIO_Port GPIOD
#define FDCAN1_RX_Pin GPIO_PIN_3
#define FDCAN1_RX_GPIO_Port GPIOB
#define FDCAN1_TX_Pin GPIO_PIN_4
#define FDCAN1_TX_GPIO_Port GPIOB
#define NMES_ACU_CS_Pin GPIO_PIN_7
#define NMES_ACU_CS_GPIO_Port GPIOB
#define CHARGER_DETECT_Pin GPIO_PIN_9
#define CHARGER_DETECT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
