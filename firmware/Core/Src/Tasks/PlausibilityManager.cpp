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
extern GpioIn  pre_AIR;

// FIXME to remove after testing/debuging
bool ts_act_test = {false};
AIRstateEnum test_air_state;

void vPlausibilityManagerTask(void *argument)
{
	PlausibilityChecker checker(FullStackDataInstance::get());
	AccumulatorIsolationRelaySM AIRsm;
	AIRdriver airs;


	while (true)
	{
		osDelay(10);
		led_ok.toggle();

		// AIRs
		auto ts_allowed = pre_AIR.isActive(); // and no error;
		AIRsm.set_TS(ts_allowed);
		AIRsm.update(HAL_GetTick());
		airs.SetState(AIRsm.get());
		test_air_state = AIRsm.get();


		if(FullStackDataInstance::get().state.ts_activation_button or ts_act_test){
			AIRsm.TS_activation_button(HAL_GetTick());
			FullStackDataInstance::set().state.ts_activation_button = false;
		}




		Checks::ErrorOrWarning optonalError = checker.check();
		if (not optonalError.has_value())
		{
			continue;
		}

		if (std::holds_alternative<Checks::CriticalError>(*optonalError))
		{
			FullStackDataInstance::set().state.error = std::get<Checks::CriticalError>(*optonalError);
			// TODO AMS fault pin high
		}
		else
		{
			FullStackDataInstance::set().state.warning = std::get<Checks::Warning>(*optonalError);
		}
	}
}
