/*
 * LTCManager.cpp
 *
 *  Created on: Jul 1, 2023
 *      Author: Piotr Lesicki
 */

#include "app_freertos.h"
#include "main.h"
#include "PerypherialManagers/LTCController.hpp"
#include "PerypherialManagers/Gpio.hpp"

static SPI_HandleTypeDef * hspi = &hspi2;

void vLTCManagerTask(void *argument)
{
	LTCController ltc_ctrl(GpioOut(NLTC2_CS_GPIO_Port, NLTC2_CS_Pin, true), hspi);
	while(true)
	{
		osDelay(100);
	}

}
