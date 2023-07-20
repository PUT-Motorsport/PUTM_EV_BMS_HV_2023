/*
 * LoggerManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: piotr
 */

#include "app_freertos.h"
#include "main.h"
#include "PerypherialManagers/SpiDmaManager.hpp"

void vLoggerManagerTask(void *argument)
{
	while(true)
	{
		osDelay(100);
	}
}


