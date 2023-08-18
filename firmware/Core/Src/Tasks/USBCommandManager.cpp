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
	embeddedjson::Json<3000> json;
	json.add("hejka", 12);

	auto [array, size] = json.get_as_c_array();

	while(true)
	{
		uint8_t status = CDC_Transmit_FS((uint8_t*)array, size);
		osDelay(1000);
	}
}


