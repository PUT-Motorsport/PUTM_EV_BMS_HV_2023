/*
 * LoggerManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: piotr
 */

#include <main.h>

#include <app_freertos.h>
#include <StackData.hpp>

void vLoggerManagerTask(void *argument)
{
  osDelay(2000);
  HAL_GPIO_WritePin(AMS_FAULT_GPIO_Port, AMS_FAULT_Pin, GPIO_PIN_SET);
	while(true)
	{
		osDelay(100);
	}
}


