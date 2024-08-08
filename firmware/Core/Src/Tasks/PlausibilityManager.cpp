/*
 * PlausibilityManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Jan Węgrzynowski
 */

#include <main.h>
#include <app_freertos.h>
#include <StackData.hpp>
#include <PerypherialManagers/AirSM.hpp>
#include <PerypherialManagers/GpioController.hpp>
#include <PerypherialManagers/PlausibilityCheckerController.hpp>
#include <PerypherialManagers/AIRdriver.hpp>

extern GpioOut led_ok;
extern GpioOut led_warning;
extern GpioOut led_error;
extern GpioOut ams_status;
extern GpioIn  safety_detect;

void vPlausibilityManagerTask(void *argument)
{
	PlausibilityChecker checker(FullStackDataInstance::get());
	AccumulatorIsolationRelaySM AIRsm;
	AIRdriver airs;
	auto& fsd = FullStackDataInstance::set();

	bool ams_fault { false };

	while (true)
	{
		osDelay(10);
		ams_status.toggle();

		if(HAL_GetTick() < 2'850)
		{
			led_error.activate();
			continue;
		}
		else
		{
			led_error.deactivate();
		}

		// AIRs
		AIRsm.set_TS(fsd.external_data.safety_state);
		AIRsm.update(HAL_GetTick());
		airs.SetState(AIRsm.get());

		// Time update for some checks
		fsd.time.tick = HAL_GetTick();

		//const bool charger_mode = fsd.charger.charged_detected;
		//fsd.state.ts_activation_button = true;
		if(fsd.state.ts_activation_button && AIRsm.get() == AIRstateEnum::Open)
		{
			AIRsm.TS_activation_button(HAL_GetTick());
			fsd.state.ts_activation_button = false;
		}

		fsd.state.list_of_errors = checker.get_error_list();

		Checks::OptionalError optonalError = checker.check();
		if (not optonalError.has_value())
		{
			continue;
		}
		else
		{
			auto error = (*optonalError);
			fsd.state.error = error;
			ams_fault = true;
		}

	}
}
