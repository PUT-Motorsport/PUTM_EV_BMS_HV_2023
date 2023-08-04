/*
 * PlausibilityChecker.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_
#define INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_

#include <MainHeader.hpp>

class PlausibilityChecker
{
private:
	const FullStackData &stackData;

	// TODO: add more checks
	const std::array<CHECKS::ErrorOrWarning (*)(const FullStackData &), 4> checks{
		CHECKS::underVoltage,
		CHECKS::overVoltage,
		CHECKS::underTemperature,
		CHECKS::overTemperature,
	};

public:
	PlausibilityChecker(const FullStackData &stackData) : stackData(stackData)
	{
	}

	constexpr CHECKS::ErrorOrWarning check() const
	{
		for (const auto check : checks)
		{
			CHECKS::ErrorOrWarning evaluatedCheck = check(stackData);
			if (evaluatedCheck.has_value())
			{
				return evaluatedCheck.value();
			}
		}
		return std::nullopt;
	}
};

#endif /* INC_PERYPHERIALMANAGERS_PLAUSIBILITYCHECKERCONTROLLER_HPP_ */
