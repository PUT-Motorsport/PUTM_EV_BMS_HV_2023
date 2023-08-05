/*
 * Config.hpp
 *
 *  Created on: 3 sie 2023
 *      Author: piotr
 */

#ifndef INC_INTERFACES_CONFIG_HPP_
#define INC_INTERFACES_CONFIG_HPP_

#include "main.h"

//ltc
namespace Ltc
{
	static constexpr size_t CHAIN_SIZE = 15;
	static constexpr float UNDERVOLTAGE = 2.f;
	static constexpr float OVERVOLTAGE = 4.f;

	static constexpr size_t CELL_COUNT = CHAIN_SIZE * 9;
	static constexpr size_t TEMP_COUNT = CHAIN_SIZE * 3;
}

namespace Checks
{
	constexpr static float CELL_MAX_VOLTAGE = 4.175f;
	constexpr static float CELL_MIN_VOLTAGE = 3.0f;
	constexpr static float CELL_MAX_TEMPERATURE = 50.0f;
	constexpr static float CELL_MIN_TEMPERATURE = -20.0f;
}
#endif /* INC_INTERFACES_CONFIG_HPP_ */
