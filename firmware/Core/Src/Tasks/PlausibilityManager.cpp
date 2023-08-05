/*
 * PlausibilityManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Jan Węgrzynowski
 */

#include <main.h>

#include <app_freertos.h>
#include <StackData.hpp>
#include <PerypherialManagers/GpioController.hpp>
#include <PerypherialManagers/PlausibilityCheckerController.hpp>

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
		led_ok.toggle();

		CHECKS::ErrorOrWarning optonalError = checker.check();
		if (not optonalError.has_value())
		{
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
