/*
 * USBCommandManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <main.h>

#include <app_freertos.h>
#include <StackData.hpp>
#include <usb_device.h>
#include <usbd_cdc_if.h>
#include <string.h>

#include "embedded_json/include/embedded_json.hpp"

// https://community.st.com/t5/embedded-software-mcus/way-to-be-notified-on-cdc-transmit-complete/td-p/412336

void vUSBCommandManagerTask(void *argument)
{
	std::array<float, 135> cell_voltage = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
						        16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
						        31.0, 32.0, 33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0, 45.0,
						        46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0, 57.0, 58.0, 59.0, 60.0,
						        61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0, 69.0, 70.0, 71.0, 72.0, 73.0, 74.0, 75.0,
						        76.0, 77.0, 78.0, 79.0, 80.0, 81.0, 82.0, 83.0, 84.0, 85.0, 86.0, 87.0, 88.0, 89.0, 90.0,
						        91.0, 92.0, 93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0, 100.0, 101.0, 102.0, 103.0, 104.0, 105.0,
						        106.0, 107.0, 108.0, 109.0, 110.0, 111.0, 112.0, 113.0, 114.0, 115.0, 116.0, 117.0, 118.0, 119.0, 120.0,
						        121.0, 122.0, 123.0, 124.0, 125.0, 126.0, 127.0, 128.0, 129.0, 130.0, 131.0, 132.0, 133.0, 134.0, 135.0
	};

	std::array<float, 45> temperature = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
	        16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0,
	        31.0, 32.0, 33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0, 45.0};

	static constexpr size_t max_size = 3000;
	embeddedjson::Json<max_size > json;
	json.add("current", 1.0f);
	json.add("acc_voltage", 2.0f);
	json.add("car_voltage", 3.0f);
	json.add("soc", 3.0f);
	json.add("cell_voltage", cell_voltage);
	json.add("temperature", temperature);

	auto [array, size] = json.get_as_c_array();

	while(true)
	{
		while(CDC_Transmit_FS((uint8_t*)array, size) == USBD_BUSY)
		{
			osDelay(1);
		}
		osDelay(1000);
	}
}


