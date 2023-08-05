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

class PlausibilityChecker
{
private:
	const FullStackData &stackData;

	// TODO: add more checks
	const std::array<Checks::ErrorOrWarning (*)(const FullStackData &), 4> checks{
		Checks::underVoltage,
		Checks::overVoltage,
		Checks::underTemperature,
		Checks::overTemperature,
	};

public:
	PlausibilityChecker(const FullStackData &stackData) : stackData(stackData)
	{
	}

	constexpr Checks::ErrorOrWarning check() const
	{
		for (const auto check : checks)
		{
			Checks::ErrorOrWarning evaluatedCheck = check(stackData);
			if (evaluatedCheck.has_value())
			{
				return evaluatedCheck.value();
			}
		}
		return std::nullopt;
	}
};

#endif /* INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_ */
