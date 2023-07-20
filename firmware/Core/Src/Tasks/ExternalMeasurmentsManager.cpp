/*
 * ExternalMeasurmentsManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include "PerypherialManagers/SpiDmaManager.hpp"
#include "PerypherialManagers/MCP356x.hpp"
#include "app_freertos.h"
#include "spi.h"
#include "etl/array.h"
#include "main.h"

const size_t num_of_dev = 3;

static SPI_HandleTypeDef * hspi = &hspi3;

extern GpioOut led_warning;

void vExternalMeasurmentsManagerTask(void *argument)
{
	MCP3561x car(GpioOut(NMES_CAR_CS_GPIO_Port, NMES_CAR_CS_Pin, true), hspi, MCP356xVersion::MCP3561);
	MCP3561x acu(GpioOut(NMES_ACU_CS_GPIO_Port, NMES_ACU_CS_Pin, true), hspi, MCP356xVersion::MCP3561);
	MCP3561x isens(GpioOut(NMES_ISENS_CS_GPIO_Port, NMES_ISENS_CS_Pin, true), hspi, MCP356xVersion::MCP3562);

	etl::array< MCP3561x*, num_of_dev > devices = { &car, &acu, &isens };

	while(true)
	{
		for (auto dev : devices)
			dev->poolSatusByte();

		osDelay(100);
	}
}


