/*
 * PlausibilityChecker.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_CONTROLLERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_
#define INC_CONTROLLERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_

#include <Controllers/ChecksController.hpp>
#include <main.h>
#include <array>

#include <Interfaces/StateErrorWarning.hpp>
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

	mutable std::array<Checks::ErrorListElement, checks.size()> errors{
		Checks::ErrorListElement{ Checks::CriticalError{CriticalErrorsEnum::UnderVoltage,0}, false},
		Checks::ErrorListElement{ Checks::CriticalError{CriticalErrorsEnum::OverVoltage,0}, false},
		Checks::ErrorListElement{ Checks::CriticalError{CriticalErrorsEnum::UnderTemperature,0}, false},
		Checks::ErrorListElement{ Checks::CriticalError{CriticalErrorsEnum::OverTemperature,0}, false},
		Checks::ErrorListElement{ Checks::CriticalError{CriticalErrorsEnum::OverCurrent,0}, false},
		Checks::ErrorListElement{ Checks::CriticalError{CriticalErrorsEnum::CurrentSensorDisconnected,0}, false},
	};

public:
	constexpr PlausibilityChecker(const FullStackData &stackData) : stackData(stackData) { }

	constexpr static size_t size()
	{
		return checks.size();
	}

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
				if(not errors[i].second)
				{
					errors[i] = Checks::ErrorListElement{evaluatedCheck.value(), true};
				}

			}
			++i;
		}
		return ret;
	}

	constexpr std::array<Checks::ErrorListElement, checks.size()> get_error_list() const{
		return errors;
	}
};

#endif /* INC_CONTROLLERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_ */
