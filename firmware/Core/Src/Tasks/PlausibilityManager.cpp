/*
 * PlausibilityManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include "app_freertos.h"
#include "main.h"
#include "PerypherialManagers/Gpio.hpp"
#include "PerypherialManagers/PlausibilityChecker.hpp"

extern GpioOut led_ok;
extern GpioOut led_warning;
extern GpioOut led_error;

void vPlausibilityManagerTask(void *argument)
{
	while(true)
	{
		led_ok.toggle();
		osDelay(100);
	}
}
