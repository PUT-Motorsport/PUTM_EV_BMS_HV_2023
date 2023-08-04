/*
 * ExternalMeasurmentsManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <PerypherialManagers/MCP356Controller.hpp>
#include <PerypherialManagers/SpiDmaController.hpp>
#include "app_freertos.h"
#include "spi.h"
#include "etl/array.h"
#include "main.h"
#include "StackData.hpp"

static SPI_HandleTypeDef &hspi = hspi3;

extern GpioOut led_warning;
extern GpioIn charger_conected;

void vExternalMeasurmentsManagerTask(void *argument)
{
	MCP356Controller car(GpioOut(NMES_CAR_CS_GPIO_Port, NMES_CAR_CS_Pin, true), hspi, MCP356xVersion::MCP3561);
	MCP356Controller acu(GpioOut(NMES_ACU_CS_GPIO_Port, NMES_ACU_CS_Pin, true), hspi, MCP356xVersion::MCP3561);
	MCP356Controller isens(GpioOut(NMES_ISENS_CS_GPIO_Port, NMES_ISENS_CS_Pin, true), hspi, MCP356xVersion::MCP3562);

	etl::array< MCP356Controller*, 3 > devices = { &car, &acu, &isens };

	while(true)
	{
		FullStackDataInstance::getAndModify().ltc_data.charger_connected = charger_conected.isActive();
		for (auto dev : devices)
			dev->poolSatusByte();

		osDelay(100);
	}
}


