/*
 * LoggerManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: piotr
 */

#include <PerypherialManagers/SpiDmaController.hpp>
#include "app_freertos.h"
#include "main.h"

void vLoggerManagerTask(void *argument)
{
	while(true)
	{
		osDelay(100);
	}
}


