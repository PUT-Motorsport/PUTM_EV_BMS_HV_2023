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
	while(true)
	{
		osDelay(10000);
	}
}


