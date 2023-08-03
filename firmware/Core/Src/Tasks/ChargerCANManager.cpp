/*
 * ChargerCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: jan
 */

#include "PerypherialManagers/CanUtils.hpp"
#include "PerypherialManagers/Charger.hpp"
#include "app_freertos.h"
#include "fdcan.h"
#include "main.h"

static FDCAN_HandleTypeDef &hfdcan = hfdcan2;

bool charger_connected()
{
	return not HAL_GPIO_ReadPin(CHARGER_DETECT_GPIO_Port, CHARGER_DETECT_Pin);
}

void vChargerCANManagerTask(void *argument)
{
	startCan(hfdcan);
	bool charging_enable{false};
	float charge_voltage = 135.0f * 4.15f;
	float charge_current = 2.0f;
	ChargerCanRxMessageHandler charger_rx{};

	while (true)
	{
		if (charger_connected())
		{
			osDelay(100);

			// TODO select balance cell

			// TODO change charing current if balancing

			while (get_can_fifo_message_count(hfdcan))
			{
				charger_rx.update();
			}
			ChargerCanTxMessage frame{charge_voltage, charge_current, charging_enable};
			frame.send();
		}
		else
		{
			osDelay(1000);
		}
	}
}
