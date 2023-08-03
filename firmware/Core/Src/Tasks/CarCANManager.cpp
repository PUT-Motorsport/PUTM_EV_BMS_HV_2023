/*
 * CarCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: jan
 */

#include "PerypherialManagers/CanUtils.hpp"
#define PUTM_USE_CAN_FD
#include "PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp"
#include "app_freertos.h"
#include "fdcan.h"
#include "main.h"

static FDCAN_HandleTypeDef &hfdcan = hfdcan3;

void vCarCANManagerTask(void *argument)
{
	startCan(hfdcan);
	while (true)
	{
		osDelay(5);
		while (get_can_fifo_message_count(hfdcan))
		{
			PUTM_CAN::can.parse_message(PUTM_CAN::Can_rx_message(hfdcan));
		}
	}
}
