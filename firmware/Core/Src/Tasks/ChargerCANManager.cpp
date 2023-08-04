/*
 * ChargerCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: jan
 */

#include <MainHeader.hpp>

static FDCAN_HandleTypeDef &hfdcan = hfdcan2;
extern GpioIn charger_conected;

void vChargerCANManagerTask(void *argument)
{
	startCan(hfdcan);

	ChargeBalanceController balanceController(FullStackDataInstance::getAndModify());
	balanceController.disable_balance();

	bool charging_enable{false};
	float charge_voltage = 135.0f * 4.15f;
	float charge_current = 2.0f;
	ChargerCanRxMessageHandler charger_rx{};

	while (true)
	{
		if (FullStackDataInstance::get().ltc_data.charger_connected)
		{
			continue;
		}

		balanceController.update();

		while (getCanFifoMessageCount(hfdcan))
		{
			charger_rx.update();
		}
		ChargerCanTxMessage frame{charge_voltage, charge_current, charging_enable};
		frame.send();
	}
}
