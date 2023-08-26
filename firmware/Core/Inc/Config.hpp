/*
 * Config.hpp
 *
 *  Created on: 3 sie 2023
 *      Author: piotr
 */

#ifndef INC_INTERFACES_CONFIG_HPP_
#define INC_INTERFACES_CONFIG_HPP_

#include <main.h>

#include <Interfaces/MCP356xRegs.hpp>

namespace LtcConfig
{
	static constexpr size_t CHAIN_SIZE = 15;
	static constexpr float UNDERVOLTAGE = 2.f;
	static constexpr float OVERVOLTAGE = 4.f;

	static constexpr size_t CELL_COUNT = CHAIN_SIZE * 9;
	static constexpr size_t TEMP_COUNT = CHAIN_SIZE * 3;
}

namespace ChecksConfig
{
	constexpr static float CELL_MAX_VOLTAGE = 4.18f;
	constexpr static float CELL_MIN_VOLTAGE = 3.0f;
	constexpr static int32_t VOLTAGE_ERROR_COUNT_MAX = 40;
	constexpr static float CELL_MAX_TEMPERATURE = 55.0f;
	constexpr static float CELL_MIN_TEMPERATURE = -20.0f;
	constexpr static int32_t TEMP_ERROR_COUNT_MAX = 80;
	constexpr static float BATTERY_MAX_CURRENT = 200.0f;
	constexpr static float BATTERY_SENSOR_DISCONNECT = 350.0f;
	constexpr static int32_t CURRENT_ERROR_COUNT_MAX = 40;
}

namespace Mcp356xConfig
{
	constexpr static double ADC_REF_P = 3.0;
	constexpr static double ADC_REF_M = 0.0;
	constexpr static double ADC_REF = ADC_REF_P - ADC_REF_M;
}

namespace ExternalConfig
{
	constexpr static double ADC_VOLT_R = 2'000.0;
	constexpr static double ADC_VOLT_COEF = (800'000.0 + ADC_VOLT_R) / ADC_VOLT_R;
	constexpr static double ADC_CURR_COEF = 200.0 / 1.25;
}

#endif /* INC_INTERFACES_CONFIG_HPP_ */
