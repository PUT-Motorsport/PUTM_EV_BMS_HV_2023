/*
 * PlausibilityChecker.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_
#define INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_

#include <main.h>
#include <array>

#include <Interfaces/StateErrorWarning.hpp>
#include <PerypherialManagers/ChecksController.hpp>
#include <etl/utility.h>

class PlausibilityChecker
{
private:
	const FullStackData &stackData;

	constexpr static std::array<Checks::OptionalError (*)(const FullStackData &), 6> checks
	{
		Checks::underVoltage,
		Checks::overVoltage,
		Checks::underTemperature,
		Checks::overTemperature,
		Checks::overCurrent,
		Checks::CurrentSensorDisconnect
	};

	using ErrorListElement = etl::pair<Checks::CriticalError, bool>;
	std::array<ErrorListElement, checks.size()> errors{};

	size_t error_count = 0;

public:
	PlausibilityChecker(const FullStackData &stackData) : stackData(stackData) { }

	constexpr Checks::OptionalError check() const
	{
		Checks::OptionalError ret = std::nullopt;
		uint32_t i = 0;
		for (const auto& check : checks)
		{
			Checks::OptionalError evaluatedCheck = check(stackData);
			if (evaluatedCheck.has_value())
			{
				ret = evaluatedCheck.value();
				//errors[i] = ErrorListElement{evaluatedCheck.value(), true};
			}
			++i;
		}
		return ret;
	}

//	constexpr std::array<Checks::CriticalError, checks.size()> get_error_list() const{
//		return errors;
//	}
};

#endif /* INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_ */
