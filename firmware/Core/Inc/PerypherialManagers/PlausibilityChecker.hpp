/*
 * PlausibilityChecker.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKER_HPP_
#define INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKER_HPP_

#include "stackData.hpp"
#include <algorithm>
#include <cstdint>
#include <optional>
#include <ranges>
#include <utility>
#include <variant>

enum struct CriticalErrorsEnum
{
	// cell voltage
	UnderVoltage,
	OverVoltage,
	MeasurementDisconnected,

	// Cell temperature
	UnderTemperature,
	OverTemperature,
	TemperatureSensorDisconnected,

	// Whole battery current sensor
	OverCurrent,
	CurrentSensorDisconnected,

	// Whole battery voltage sensor
	OverVoltageStack,
	UnderVoltageStack,
	VoltageSensorDisconnected,

	// Battery stack
	MaintenancePlugNotConnected
};

enum struct WarningsEnum
{
	BallanceError_100mV,
	BallanceError_200mV,
};

using CriticalError = std::pair<CriticalErrorsEnum, uint8_t>; // cell number
using Warning = std::pair<WarningsEnum, uint8_t>;			  // cell number

using ErrorOrWarning = std::optional<std::variant<CriticalError, Warning>>;

class PlausibilityChecker
{
private:
	constexpr static float CELL_MAX_VOLTAGE = 4.175;
	constexpr static float CELL_MIN_VOLTAGE = 3.0;
	constexpr static float CELL_MAX_TEMPERATURE = 50;
	constexpr static float CELL_MIN_TEMPERATURE = -20;
	const FullStackData &stackData;

	constexpr ErrorOrWarning underVoltage() const
	{
		auto iterator = std::ranges::any_of(stackData.ltcData.volt, [&](auto cellVoltage)
											{ return cellVoltage < 3.0f; });
		if (iterator != stackData.ltcData.volt.end())
		{
			return std::make_pair(CriticalErrorsEnum::UnderVoltage, std::distance(stackData.ltcData.volt.begin(), iterator));
		}
	}

	constexpr ErrorOrWarning overVoltage() const
	{
		auto iterator = std::ranges::any_of(stackData.ltcData.volt, [](auto cellVoltage)
											{ return cellVoltage > CELL_MAX_VOLTAGE; });
		if (iterator != stackData.ltcData.volt.end())
		{
			return std::make_pair(CriticalErrorsEnum::OverVoltage, std::distance(stackData.ltcData.volt.begin(), iterator));
		}
	}

	// TODO: add more checks
	std::array checks {
		underVoltage,
		overVoltage,
	};

public:
	PlausibilityChecker(const FullStackData &stackData) : stackData(stackData)
	{
	}

	ErrorOrWarning check()
	{
		for (auto check : checks)
		{
			if (check.has_value())
			{
				return check;
			}
		}
		return std::nullopt;
	}
};

#endif /* INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKER_HPP_ */
