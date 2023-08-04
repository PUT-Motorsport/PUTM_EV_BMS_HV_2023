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
#include "PerypherialManagers/Gpio.hpp"
#include "StackData.hpp"

static FDCAN_HandleTypeDef &hfdcan = hfdcan2;
extern GpioIn charger_conected;

void vChargerCANManagerTask(void *argument)
{
	startCan(hfdcan);
	bool charging_enable{false};
	float charge_voltage = 135.0f * 4.15f;
	float charge_current = 2.0f;
	ChargerCanRxMessageHandler charger_rx{};

	while (true)
	{
		if (FullStackDataInstance::get().ltc_data.charger_connected)
		{
			osDelay(100);

			// TODO select balance cell

			// TODO change charing current if balancing

			while (getCanFifoMessageCount(hfdcan))
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
