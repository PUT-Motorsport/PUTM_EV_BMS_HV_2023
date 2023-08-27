/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_freertos.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for PlausibilityManager */
osThreadId_t PlausibilityManagerHandle;
uint32_t PlausibilityManagerBuffer[ 1024 ];
osStaticThreadDef_t PlausibilityManagerControlBlock;
const osThreadAttr_t PlausibilityManager_attributes = {
  .name = "PlausibilityManager",
  .stack_mem = &PlausibilityManagerBuffer[0],
  .stack_size = sizeof(PlausibilityManagerBuffer),
  .cb_mem = &PlausibilityManagerControlBlock,
  .cb_size = sizeof(PlausibilityManagerControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LTCManager */
osThreadId_t LTCManagerHandle;
uint32_t LTCManagerBuffer[ 1024 ];
osStaticThreadDef_t LTCManagerControlBlock;
const osThreadAttr_t LTCManager_attributes = {
  .name = "LTCManager",
  .stack_mem = &LTCManagerBuffer[0],
  .stack_size = sizeof(LTCManagerBuffer),
  .cb_mem = &LTCManagerControlBlock,
  .cb_size = sizeof(LTCManagerControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ExternalMeasurmentsManager */
osThreadId_t ExternalMeasurmentsManagerHandle;
uint32_t ExternalMeasurmentsManagerBuffer[ 1024 ];
osStaticThreadDef_t ExternalMeasurmentsManagerControlBlock;
const osThreadAttr_t ExternalMeasurmentsManager_attributes = {
  .name = "ExternalMeasurmentsManager",
  .stack_mem = &ExternalMeasurmentsManagerBuffer[0],
  .stack_size = sizeof(ExternalMeasurmentsManagerBuffer),
  .cb_mem = &ExternalMeasurmentsManagerControlBlock,
  .cb_size = sizeof(ExternalMeasurmentsManagerControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LoggerManager */
osThreadId_t LoggerManagerHandle;
uint32_t LoggerManagerrBuffer[ 1024 ];
osStaticThreadDef_t LoggerManagerrControlBlock;
const osThreadAttr_t LoggerManager_attributes = {
  .name = "LoggerManager",
  .stack_mem = &LoggerManagerrBuffer[0],
  .stack_size = sizeof(LoggerManagerrBuffer),
  .cb_mem = &LoggerManagerrControlBlock,
  .cb_size = sizeof(LoggerManagerrControlBlock),
  .priority = (osPriority_t) osPriorityLow4,
};
/* Definitions for USBCommandManager */
osThreadId_t USBCommandManagerHandle;
uint32_t myTask05Buffer[ 1024 ];
osStaticThreadDef_t myTask05ControlBlock;
const osThreadAttr_t USBCommandManager_attributes = {
  .name = "USBCommandManager",
  .stack_mem = &myTask05Buffer[0],
  .stack_size = sizeof(myTask05Buffer),
  .cb_mem = &myTask05ControlBlock,
  .cb_size = sizeof(myTask05ControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CarCANManager */
osThreadId_t CarCANManagerHandle;
uint32_t CarCANManagerBuffer[ 1024 ];
osStaticThreadDef_t CarCANManagerControlBlock;
const osThreadAttr_t CarCANManager_attributes = {
  .name = "CarCANManager",
  .stack_mem = &CarCANManagerBuffer[0],
  .stack_size = sizeof(CarCANManagerBuffer),
  .cb_mem = &CarCANManagerControlBlock,
  .cb_size = sizeof(CarCANManagerControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ChargerCANManager */
osThreadId_t ChargerCANManagerHandle;
uint32_t ChargerCANManagerBuffer[ 1024 ];
osStaticThreadDef_t ChargerCANManagerControlBlock;
const osThreadAttr_t ChargerCANManager_attributes = {
  .name = "ChargerCANManager",
  .stack_mem = &ChargerCANManagerBuffer[0],
  .stack_size = sizeof(ChargerCANManagerBuffer),
  .cb_mem = &ChargerCANManagerControlBlock,
  .cb_size = sizeof(ChargerCANManagerControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SOCManager */
osThreadId_t SOCManagerHandle;
uint32_t SOCManagerBuffer[ 1024 ];
osStaticThreadDef_t SOCManagerControlBlock;
const osThreadAttr_t SOCManager_attributes = {
  .name = "SOCManager",
  .stack_mem = &SOCManagerBuffer[0],
  .stack_size = sizeof(SOCManagerBuffer),
  .cb_mem = &SOCManagerControlBlock,
  .cb_size = sizeof(SOCManagerControlBlock),
  .priority = (osPriority_t) osPriorityBelowNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void vPlausibilityManagerTask(void *argument);
extern void vLTCManagerTask(void *argument);
extern void vExternalMeasurmentsManagerTask(void *argument);
extern void vLoggerManagerTask(void *argument);
extern void vUSBCommandManagerTask(void *argument);
extern void vCarCANManagerTask(void *argument);
extern void vChargerCANManagerTask(void *argument);
extern void vSOCManagerTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of PlausibilityManager */
  PlausibilityManagerHandle = osThreadNew(vPlausibilityManagerTask, NULL, &PlausibilityManager_attributes);

  /* creation of LTCManager */
  LTCManagerHandle = osThreadNew(vLTCManagerTask, NULL, &LTCManager_attributes);

  /* creation of ExternalMeasurmentsManager */
  ExternalMeasurmentsManagerHandle = osThreadNew(vExternalMeasurmentsManagerTask, NULL, &ExternalMeasurmentsManager_attributes);

  /* creation of LoggerManager */
  LoggerManagerHandle = osThreadNew(vLoggerManagerTask, NULL, &LoggerManager_attributes);

  /* creation of USBCommandManager */
  USBCommandManagerHandle = osThreadNew(vUSBCommandManagerTask, NULL, &USBCommandManager_attributes);

  /* creation of CarCANManager */
  CarCANManagerHandle = osThreadNew(vCarCANManagerTask, NULL, &CarCANManager_attributes);

  /* creation of ChargerCANManager */
  ChargerCANManagerHandle = osThreadNew(vChargerCANManagerTask, NULL, &ChargerCANManager_attributes);

  /* creation of SOCManager */
  SOCManagerHandle = osThreadNew(vSOCManagerTask, NULL, &SOCManager_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_vPlausibilityManagerTask */
/**
  * @brief  Function implementing the PlausibilityManager thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_vPlausibilityManagerTask */
__weak void vPlausibilityManagerTask(void *argument)
{
  /* USER CODE BEGIN vPlausibilityManagerTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END vPlausibilityManagerTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

