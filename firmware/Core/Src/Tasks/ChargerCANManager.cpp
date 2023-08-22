/*
 * ChargerCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Jan
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
static std::array<float, 135> temperature{};
static std::array<float, 135> soc{};
#endif

// FIXME move inside the task
static ChargerCanRxMessageHandler charger_rx{};



void vChargerCANManagerTask(void *argument)
{
	constexpr static float charge_voltage = 135.0f * 4.15f;
	startCan(hfdcan);

	ChargeBalanceController balanceController(FullStackDataInstance::set());
	balanceController.disableBalance();

	uint32_t balance_start{HAL_GetTick()};
	bool balance_toggle = false;

	while (true)
	{
		osDelay(200);

		std::ranges::copy(FullStackDataInstance::get().ltc_data.voltages.begin(),
						  FullStackDataInstance::get().ltc_data.voltages.end(), voltages.begin());

		std::ranges::copy(FullStackDataInstance::get().ltc_data.temp_C.begin(),
						  FullStackDataInstance::get().ltc_data.temp_C.end(), temperature.begin());

		std::ranges::copy(FullStackDataInstance::get().soc.cells_soc.begin(),
						  FullStackDataInstance::get().soc.cells_soc.end(), soc.begin());

		balanceController.update();

		FullStackDataInstance::set().charger.charged_detected = not HAL_GPIO_ReadPin(CHARGER_DETECT_GPIO_Port, CHARGER_DETECT_Pin);

		if (not FullStackDataInstance::get().charger.charged_detected)
		{
			continue;
		}


		constexpr static size_t BALANCE_TIME = 7'000;
		if(HAL_GetTick() > balance_start + BALANCE_TIME){

			if(balance_toggle and FullStackDataInstance::get().charger.balance_enable
							  and not FullStackDataInstance::get().charger.charging_enable){
				balanceController.recalcBalance();
			}
			else {
		     	std::ranges::copy(FullStackDataInstance::get().ltc_data.discharge.begin(),
		     					  FullStackDataInstance::get().ltc_data.discharge.end(), discharge.begin());

				balanceController.disableBalance();
			}
			balance_toggle = not balance_toggle;
			balance_start = HAL_GetTick();
		}

		while (getCanFifoMessageCount(hfdcan))
		{
			charger_rx.update();
		}
		ChargerCanTxMessage frame{charge_voltage,
								  FullStackDataInstance::get().charger.charge_current,
								  FullStackDataInstance::get().charger.charging_enable};
		frame.send();
	}
}
