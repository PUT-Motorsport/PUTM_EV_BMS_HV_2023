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
	while (true)
	{
		osDelay(20);

		// pcb alive
		if(HAL_GetTick() < 1000)
			led_error.activate();
		else
			led_error.deactivate();

		//toggle on board watch dog
		if(not fsd.state.in_error)
		{
			ams_status.toggle();
		}
		else
		{
			led_error.activate();
		}

		// Time update for some checks
		fsd.time.tick = HAL_GetTick();

		switch (air_state)
		{
			case AirState::Open:
			{
				bool charger_on 	= fsd.usb_events.charger_on;
				bool ts_activation 	= fsd.external.ts_activation_button;
				bool tsms_on		= fsd.external.tsms_on;
				if((ts_activation or charger_on) and tsms_on)
				{
					fsd.external.ts_activation_button = false;
					air_state = AirState::Precharge;
					precharge_start = HAL_GetTick();
				}
			} break;
			case AirState::Precharge:
			{
				//FIXM: preferably it should be the external acu mes
				float pre_charge_margin = fsd.ltc.bat_volt * 0.95f;
				float pre_charge		= fsd.external.car_volt;
				float bat_min_voltage	= LtcConfig::CELL_COUNT * ChecksConfig::CELL_MIN_VOLTAGE;
				bool in_error			= fsd.state.in_error;
				bool charger_on 		= fsd.usb_events.charger_on;
				uint32_t time 			= HAL_GetTick();
				uint32_t finish_time	= precharge_start + PlausibilityConfig::min_precharge_time;
				if((pre_charge > pre_charge_margin) and (time > finish_time) and pre_charge_margin > bat_min_voltage)
				{
					air_state = AirState::Closed;
				}
				else if (in_error or not charger_on)
				{
					air_state = AirState::Open;
				}
			} break;
			case AirState::Closed:
			{
				bool tsms_on	= fsd.external.tsms_on;
				bool charger_on = fsd.usb_events.charger_on;
				bool in_error	= fsd.state.in_error;
				if(in_error or not tsms_on or not charger_on)
				{
					air_state = AirState::Open;
				}
			} break;
		}

		air_driver.setState(air_state);

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
			fsd.state.in_error = true;
		}

	}
}
