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


void AMS_LIGHT(bool on){
	HAL_GPIO_WritePin(FAN_CTRL1_GPIO_Port, FAN_CTRL1_Pin, GPIO_PinState(on));
	if(on){
		led_error.activate();
	}
	else {
		led_error.deactivate();
	}
}

void AMS_FAULT(){
	HAL_GPIO_WritePin(AMS_FAULT_GPIO_Port, AMS_FAULT_Pin, GPIO_PIN_SET);
	AMS_LIGHT(true);
}

void vPlausibilityManagerTask(void *argument)
{
	PlausibilityChecker checker(FullStackDataInstance::get());
	AccumulatorIsolationRelaySM AIRsm;
	AIRdriver airs;
	auto& fsd = FullStackDataInstance::set();

	bool ams_fault{false};

	while (true)
	{
		osDelay(10);
		led_ok.toggle();

		if(HAL_GetTick() < 2'850){ //ms
			AMS_LIGHT(true);
			continue;
		}
		else {
			AMS_LIGHT(ams_fault);
		}

		// AIRs
		auto ts_allowed = pre_AIR.isActive();
		AIRsm.set_TS(ts_allowed);
		AIRsm.update(HAL_GetTick());
		airs.SetState(AIRsm.get());

		// Time update for some checks
		fsd.time.tick = HAL_GetTick();

		const bool charger_mode = fsd.charger.charged_detected;
		if(fsd.state.ts_activation_button or charger_mode){
			AIRsm.TS_activation_button(HAL_GetTick());
			fsd.state.ts_activation_button = false;
		}

		fsd.state.list_of_errors = checker.get_error_list();

		Checks::OptionalError optonalError = checker.check();
		if (not optonalError.has_value())
		{
			continue;
		}
		else {
			auto error = (*optonalError);
			fsd.state.error = error;
			ams_fault = true;
			AMS_FAULT();
		}

	}
}
