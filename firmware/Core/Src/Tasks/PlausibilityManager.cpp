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
#include <etl/circular_buffer.h>

extern GpioOut led_ok;
extern GpioOut led_warning;
extern GpioOut led_error;
extern GpioIn  pre_AIR;


void AMS_LIGHT(bool on){
	HAL_GPIO_WritePin(FAN_CTRL1_GPIO_Port, FAN_CTRL1_Pin, GPIO_PinState(on));
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

		const bool charger_mode = FullStackDataInstance::get().charger.charged_detected;
		if(FullStackDataInstance::get().state.ts_activation_button or charger_mode){
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
			ams_fault = true;
			AMS_FAULT();
		}
		else
		{
			FullStackDataInstance::set().state.warning = std::get<Checks::Warning>(*optonalError);
		}
	}
}
