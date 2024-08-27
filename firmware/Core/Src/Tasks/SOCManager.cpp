/*
 * SOCManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Jan Węgrzynowski
 */

#include <main.h>

#include <app_freertos.h>
#include <StackData.hpp>
#include <Config.hpp>
#include <Controllers/GpioController.hpp>
#include "SoC_EKF.h"

struct CellData
{
	Vector_col x { };
	Matrix P { };
};

static std::array<CellData, LtcConfig::CELL_COUNT> soc_array { };
static constexpr float cell_count_f = (float)LtcConfig::CELL_COUNT;

void vSOCManagerTask(void *argument)
{
	osDelay(1'000);

	for(size_t i = 0; i < LtcConfig::CELL_COUNT; ++i)
	{
		auto &cell_soc = soc_array[i];
		EKF_init(&cell_soc.x, &cell_soc.P);
		EKF_set_SoC_based_on_voltage(&cell_soc.x, FullStackDataInstance::get().ltc.voltages[i].load());
	}


	while(true)
	{
		osDelay(100);
		const float single_cell_current = FullStackDataInstance::get().external.acu_curr *  0.5f;
		const bool charging_or_balance = FullStackDataInstance::get().charger.balance_enable or
								   	   	 FullStackDataInstance::get().charger.charging_enable;

		for(size_t i = 0; i < LtcConfig::CELL_COUNT; ++i){
			auto &cell_soc = soc_array[i];
			const float cell_voltage = FullStackDataInstance::get().ltc.voltages[i];
			EKF_update(&cell_soc.x, &cell_soc.P, cell_voltage, single_cell_current, charging_or_balance);
			const float soc = EKF_get_SoC(&cell_soc.x);
			FullStackDataInstance::set().soc.cells_soc[i] = soc;
		}

		FullStackDataInstance::set().soc.avg = std::accumulate(FullStackDataInstance::get().soc.cells_soc.begin(),
															   FullStackDataInstance::get().soc.cells_soc.end(), 0.0f) / cell_count_f;
	}
}

void update_soc_stat(){

}
