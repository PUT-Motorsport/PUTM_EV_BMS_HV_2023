/*
 * PlausibilityManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Jan Węgrzynowski
 */

#include "PerypherialManagers/Gpio.hpp"
#include "PerypherialManagers/PlausibilityChecker.hpp"
#include "app_freertos.h"
#include "main.h"
#include "stackData.hpp"

extern GpioOut led_ok;
extern GpioOut led_warning;
extern GpioOut led_error;

// FIXME only for debug
static const FullStackData& fullstackdata_debug {FullStackDataInstance::get()};

void vPlausibilityManagerTask(void *argument)
{

	PlausibilityChecker checker(FullStackDataInstance::get());

	while (true)
	{
		osDelay(100);

		CHECKS::ErrorOrWarning optonalError = checker.check();
		if (not optonalError.has_value())
		{
			led_ok.toggle();
			continue;
		}

		if (std::holds_alternative<CHECKS::CriticalError>(*optonalError))
		{
			FullStackDataInstance::getAndModify().state.error = std::get<CHECKS::CriticalError>(*optonalError);
		}
		else
		{
			FullStackDataInstance::getAndModify().state.warning = std::get<CHECKS::Warning>(*optonalError);
		}
	}
}
