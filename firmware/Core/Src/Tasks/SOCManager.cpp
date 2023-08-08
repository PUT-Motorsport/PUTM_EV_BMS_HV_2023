/*
 * SOCManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <main.h>

#include <app_freertos.h>
#include <StackData.hpp>
#include <Config.hpp>
#include <PerypherialManagers/GpioController.hpp>

GpioOut air_p { SIG_AIR_P_GPIO_Port, SIG_AIR_P_Pin, false };
GpioOut air_m { SIG_AIR_M_GPIO_Port, SIG_AIR_M_Pin, false };
GpioOut air_pre { SIG_AIR_PRE_GPIO_Port, SIG_AIR_PRE_Pin, false };

void vSOCManagerTask(void *argument)
{
	while(true)
	{
//		air_p.toggle();
//		air_m.toggle();
//		air_pre.toggle();

		osDelay(10000);
	}
}
