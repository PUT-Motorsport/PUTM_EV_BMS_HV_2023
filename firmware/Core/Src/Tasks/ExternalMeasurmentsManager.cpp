/*
 * ExternalMeasurmentsManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <main.h>
#include <spi.h>

#include <app_freertos.h>
#include <PerypherialManagers/Mcp356xController.hpp>
#include <StackData.hpp>

//using AdcVar = MCP356x::AdcVariantAlignRightSgn;

static SPI_HandleTypeDef &hspi = hspi3;

static Mcp356xController car(GpioOut(NMES_CAR_CS_GPIO_Port, NMES_CAR_CS_Pin, true), hspi, Mcp356xVersion::MCP3561);
static Mcp356xController acu(GpioOut(NMES_ACU_CS_GPIO_Port, NMES_ACU_CS_Pin, true), hspi, Mcp356xVersion::MCP3561);
static Mcp356xController isens(GpioOut(NMES_ISENS_CS_GPIO_Port, NMES_ISENS_CS_Pin, true), hspi, Mcp356xVersion::MCP3562);

static std::array < Mcp356xController*, 3 > mcps { &car, &acu, &isens };

static Mcp356x::ConfigGroup std_config =
{
	.config0 =
	{

	},
	.config1 =
	{

	},
	.config2 =
	{

	},
	.config3 =
	{

	}
};

static GpioIn charger_conected { CHARGER_DETECT_GPIO_Port, CHARGER_DETECT_Pin };
static GpioIn safety_detect { SAFETY_DETECT_GPIO_Port, SAFETY_DETECT_Pin };
static GpioIn air_pre_detect { AIR_PRE_DETECT_GPIO_Port, AIR_PRE_DETECT_Pin };
static GpioIn air_p_detect { AIR_P_DETECT_GPIO_Port, AIR_P_DETECT_Pin };
static GpioIn air_m_detect { AIR_M_DETECT_GPIO_Port, AIR_M_DETECT_Pin };

void vExternalMeasurmentsManagerTask(void *argument)
{
	for(auto mcp : mcps)
	{
		mcp->configure(std_config);
	}

	car.setChannels(Mcp356x::MuxIn::Ch0, Mcp356x::MuxIn::Ch1);
	acu.setChannels(Mcp356x::MuxIn::Ch0, Mcp356x::MuxIn::Ch1);
	isens.setChannels(Mcp356x::MuxIn::Ch2, Mcp356x::MuxIn::Ch3);

	while(true)
	{
		FullStackDataInstance::set().ltc_data.charger_connected = charger_conected.isActive();
		FullStackDataInstance::set().air.m_state = air_m_detect.isActive();
		FullStackDataInstance::set().air.p_state = air_p_detect.isActive();
		FullStackDataInstance::set().air.pre_state = air_pre_detect.isActive();

		osDelay(100);
	}
}


