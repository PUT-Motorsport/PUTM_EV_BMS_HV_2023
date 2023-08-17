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


// https://community.st.com/t5/embedded-software-mcus/way-to-be-notified-on-cdc-transmit-complete/td-p/412336

static const char *data = "Hello World!\r\n";

void vUSBCommandManagerTask(void *argument)
{

	while(true)
	{
    // Pack data into 64 byte buffer // TODO: Check if it fits our data
    // Transmit data

    // To imlement this in the INTERRUPT context we have to mess up with the HAL libraries
		// This only queues the data:
    uint8_t status = CDC_Transmit_FS((uint8_t*)data, strlen(data));

    // This is a callback that has to be implemented in usbd_cdc_if.c
    // CDC_Receive_FS();


    osDelay(1000);
	}
}


