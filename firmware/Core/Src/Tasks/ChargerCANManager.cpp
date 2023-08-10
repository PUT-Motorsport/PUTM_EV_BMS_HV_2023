/*
 * ChargerCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: jan
 */

#include <main.h>
#include <fdcan.h>

#include <app_freertos.h>
#include <StackData.hpp>
#include <Utils/CanUtils.hpp>
#include <PerypherialManagers/GpioController.hpp>
#include <PerypherialManagers/ChargeBalanceController.hpp>
#include <PerypherialManagers/ChargerController.hpp>

static FDCAN_HandleTypeDef &hfdcan = hfdcan2;

void vChargerCANManagerTask(void *argument)
{
	startCan(hfdcan);

	ChargeBalanceController balanceController(FullStackDataInstance::set());
	balanceController.disableBalance();

	bool charging_enable{false};
	float charge_voltage = 135.0f * 4.15f;
	float charge_current = 2.0f;
	ChargerCanRxMessageHandler charger_rx{};

	while (true)
	{
//		if (not FullStackDataInstance::get().ltc_data.charger_connected)
//		{
//			continue;
//		}

		balanceController.update();
		balanceController.recalcBalance();
		osDelay(5000);
		balanceController.disableBalance();
		osDelay(5000);

//		while (getCanFifoMessageCount(hfdcan))
//		{
//			charger_rx.update();
//		}
//		ChargerCanTxMessage frame{charge_voltage, charge_current, charging_enable};
//		frame.send();
	}
}
