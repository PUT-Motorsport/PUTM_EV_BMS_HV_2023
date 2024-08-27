/*
 * PlausibilityManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Jan Węgrzynowski
 */

#include <main.h>
#include <app_freertos.h>
#include <Controllers/GpioController.hpp>
#include <Controllers/PlausibilityCheckerController.hpp>
#include <StackData.hpp>
#include <Controllers/AirController.hpp>

extern GpioOut led_ok;
extern GpioOut led_warning;
extern GpioOut led_error;
extern GpioOut ams_status;

static AirState air_state { AirState::Open };

static uint32_t precharge_start { 0 };

static auto& fsd = FullStackDataInstance::set();

static AirController air_driver;

static PlausibilityChecker checker(FullStackDataInstance::get());

void vPlausibilityManagerTask(void *argument)
{
	ams_status.activate();
	while (true)
	{
		osDelay(20);

		// pcb alive
		if(HAL_GetTick() < 1000)
			led_ok.activate();
		else
			led_ok.deactivate();

		//toggle on board watch dog
		if(not fsd.state.in_error)
		{
			ams_status.activate();
		}
		else
		{
			ams_status.deactivate();
			led_error.activate();
		}

		// Time update for some checks
		fsd.time.tick = HAL_GetTick();

		// reset ts_activation if tsms is not present
		if(not fsd.external.tsms_on)
		{
			fsd.external.ts_activation_button = false;
		}

		switch (air_state)
		{
			case AirState::Open:
			{
				bool charger_connected 	= fsd.external.charger_connected;
				bool ts_activation 		= fsd.external.ts_activation_button;
				bool tsms_on			= fsd.external.tsms_on;
				bool in_error			= fsd.state.in_error;

				if((ts_activation or charger_connected) and tsms_on and not in_error)
				{
					fsd.external.ts_activation_button 	= false;
					air_state 							= AirState::Precharge;
					precharge_start 					= HAL_GetTick();
				}
			} break;
			case AirState::Precharge:
			{
				//FIXME: preferably it should be the external acu mes
				float bat_min_voltage	= LtcConfig::CELL_COUNT * ChecksConfig::CELL_MIN_VOLTAGE;
				float pre_charge_margin = std::max(fsd.ltc.bat_volt * PlausibilityConfig::precharge_min_charge, bat_min_voltage);
				float pre_charge		= fsd.external.car_volt;
				bool tsms_on			= fsd.external.tsms_on;
				bool in_error			= fsd.state.in_error;
				uint32_t time 			= HAL_GetTick();
				uint32_t finish_time	= precharge_start + PlausibilityConfig::min_precharge_time;

				if(not tsms_on or in_error)
				{
					air_state = AirState::Open;
					fsd.charger.charging_enable = false;
				}
				if(((pre_charge > pre_charge_margin) and time > finish_time))
				{
					air_state = AirState::Closed;
				}
			} break;
			case AirState::Closed:
			{
				bool tsms_on	= fsd.external.tsms_on;
				bool in_error	= fsd.state.in_error;
				if(not tsms_on or in_error)
				{
					air_state = AirState::Open;
					fsd.charger.charging_enable = false;
				}
			} break;
		}

		air_driver.setState(air_state);

		fsd.state.list_of_errors = checker.get_error_list();

		Checks::OptionalError optonalError = checker.check();
//		if(abs(std::max_element(fsd.ltc.voltages.begin(), fsd.ltc.voltages.end()) - std::min_element(fsd.ltc.voltages.begin(), fsd.ltc.voltages.end())) > ChecksConfig::IMBALANCE_MAX_VOLTAGE)
//		{
//			fsd.state.in_error = true;
//		}
		if (not optonalError.has_value())
		{
			continue;
		}
		else
		{
			auto error = (*optonalError);
			fsd.state.error = error;
			fsd.state.in_error = true;
		}

	}
}
