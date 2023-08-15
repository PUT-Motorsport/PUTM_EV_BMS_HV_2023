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

// FIXME only for debug
#ifdef DEBUG
static const FullStackData& fullstackdata_debug {FullStackDataInstance::get()};
static std::array<float, 135> voltages{};
static std::array<float, 135> discharge{};
#endif

void vChargerCANManagerTask(void *argument)
{
	startCan(hfdcan);

	ChargeBalanceController balanceController(FullStackDataInstance::set());
	balanceController.disableBalance();

	bool charging_enable{false};

	float charge_voltage = 135.0f * 4.15f;
	float charge_current = 2.0f;
	ChargerCanRxMessageHandler charger_rx{};

	uint32_t balance_start{};
	uint32_t balance_end{};

	while (true)
	{
		if (not FullStackDataInstance::get().ltc_data.charger_connected)
		{
			continue;
		}

     	std::ranges::copy(FullStackDataInstance::get().ltc_data.voltages.begin(),
     					  FullStackDataInstance::get().ltc_data.voltages.end(), voltages.begin());

     	FullStackDataInstance::set().ltc_data.voltages[116] = 3.8;
		balanceController.update();
		FullStackDataInstance::set().ltc_data.voltages[116] = 3.8;
		balanceController.recalcBalance();
		osDelay(10'000);

     	std::ranges::copy(FullStackDataInstance::get().ltc_data.discharge.begin(),
     					  FullStackDataInstance::get().ltc_data.discharge.end(), discharge.begin());

		balanceController.disableBalance();
		osDelay(4'000);


		// TODO with 10Hz loop frequency
		while (getCanFifoMessageCount(hfdcan))
		{
			charger_rx.update();
		}
		ChargerCanTxMessage frame{charge_voltage, charge_current, charging_enable};
		frame.send();
	}
}
