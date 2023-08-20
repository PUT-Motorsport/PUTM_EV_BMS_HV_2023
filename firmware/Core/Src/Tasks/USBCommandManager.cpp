/*
 * USBCommandManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Koza & Jan
 */

#include <main.h>

#include "embedded_json/include/embedded_json.hpp"
#include <StackData.hpp>
#include <app_freertos.h>
#include <string.h>
#include <usb_device.h>
#include <usbd_cdc_if.h>
#include <Utils/UsbUtils.hpp>

// https://community.st.com/t5/embedded-software-mcus/way-to-be-notified-on-cdc-transmit-complete/td-p/412336

extern struct UsbDataStruct usb_data;
static constexpr size_t max_size = 3000;
embeddedjson::Json<max_size> json;


void vUSBCommandManagerTask(void *argument)
{
	std::string_view test = "hahhahaahahhahahahahaloooooooo";

	while (true)
	{
		json.clear();
		json.add("current", FullStackDataInstance::get().external_data.acu_curr.load());
//		json.add("acc_voltage", FullStackDataInstance::get().external_data.acu_volt.load());
//		json.add("car_voltage", FullStackDataInstance::get().external_data.car_volt.load());
		json.add("soc", FullStackDataInstance::get().soc.cells_soc);
		json.add("cell_voltage", FullStackDataInstance::get().ltc_data.voltages);
//		json.add("temperature", FullStackDataInstance::get().ltc_data.temp);

		const auto [array, size] = json.get_as_c_array();

		while (CDC_Transmit_FS((uint8_t *)test.begin(), test.size()) == USBD_BUSY)
		{
			osDelay(10);
		}
		osDelay(1000);
	}
}
