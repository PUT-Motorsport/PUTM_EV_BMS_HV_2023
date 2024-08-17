/*
 * USBCommandManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Koza & Jan
 */

#include <main.h>

#include "embedded_json/include/embedded_json.hpp"
#include <StackData.hpp>
#include <Utils/UsbUtils.hpp>
#include <app_freertos.h>
#include <Controllers/UsbCommands.hpp>
#include <string.h>
#include <usb_device.h>
#include <usbd_cdc_if.h>
#include <Controllers/ChargerController.hpp>

//
// https://community.st.com/t5/embedded-software-mcus/way-to-be-notified-on-cdc-transmit-complete/td-p/412336
//

extern struct UsbDataStruct usb_data;
static constexpr size_t max_size = 10'000;
embeddedjson::Json<max_size> json;

void vUSBCommandManagerTask(void *argument)
{
	MX_USB_Device_Init();

	constexpr static size_t USB_TIMEOUT = 5'000;
	uint32_t usb_data_tick = HAL_GetTick();
	BMS_command_parser commands;

	while (true)
	{
		osDelay(200);

		auto message = commands.parse(usb_data.buff, usb_data.ctr);

		if (message.has_value())
		{
			switch (*message)
			{
			case Command_type::CommunicationToggle:
				usb_data_tick = HAL_GetTick();
				break;

			case Command_type::StartCharging:
				FullStackDataInstance::set().charger.charging_enable = true;
				FullStackDataInstance::set().usb_events.charger_on = true;
				break;

			case Command_type::StopCharging:
				FullStackDataInstance::set().charger.charging_enable = false;
				FullStackDataInstance::set().usb_events.charger_on = false;
				break;

			case Command_type::StartBalance:
				FullStackDataInstance::set().charger.balance_enable = true;
				break;

			case Command_type::StopBalance:
				FullStackDataInstance::set().charger.balance_enable = false;
				FullStackDataInstance::set().charger.balance_disable_tick = HAL_GetTick();
				break;

			case Command_type::SetChargeCurrent_1A:
				FullStackDataInstance::set().charger.charge_current = 1.0f;
				break;

			case Command_type::SetChargeCurrent_2A:
				FullStackDataInstance::set().charger.charge_current = 2.0f;
				break;

			case Command_type::SetChargeCurrent_4A:
				FullStackDataInstance::set().charger.charge_current = 4.0f;
				break;

			case Command_type::SetChargeCurrent_8A:
				FullStackDataInstance::set().charger.charge_current = 8.0f;
				break;

			case Command_type::SetChargeCurrent_12A:
				FullStackDataInstance::set().charger.charge_current = 12.0f;
				break;

			case Command_type::_size:
				__unreachable();
				break;
			}
		}

		if (HAL_GetTick() > usb_data_tick + USB_TIMEOUT)
		{
			continue;
		}

		json.clear();
		json.add("timestamp", (float)HAL_GetTick());
		json.add("current", FullStackDataInstance::get().external.acu_curr.load());
		json.add("acc_voltage", FullStackDataInstance::get().external.acu_volt.load());
		json.add("car_voltage", FullStackDataInstance::get().external.car_volt.load());
		json.add("soc", FullStackDataInstance::get().soc.cells_soc);
		json.add("cell_voltage", FullStackDataInstance::get().ltc.voltages);
		json.add("temperature", FullStackDataInstance::get().ltc.temp_C);

		// new
		json.add("discharge", FullStackDataInstance::get().ltc.discharge);
		json.add("balance", FullStackDataInstance::get().charger.balance_enable.load());
		json.add("charging", FullStackDataInstance::get().charger.charging_enable.load());

		for (const auto& errorEl : FullStackDataInstance::get().state.list_of_errors)
		{
			Checks::CriticalError error = errorEl.first;
			bool is_active = errorEl.second;
			CriticalErrorsEnum error_enum = error.first;
			int cell = error.second;
			json.add(Checks::ErrorNamesMap.at((size_t)error_enum), std::array{int(is_active), int(cell)});
		}

		const auto [array, size] = json.get_as_c_array();
		CDC_Transmit_FS((uint8_t *)array, size);
	}
}
