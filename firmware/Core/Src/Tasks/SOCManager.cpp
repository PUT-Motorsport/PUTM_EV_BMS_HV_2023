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
#include <PerypherialManagers/GpioController.hpp>


extern "C" {
#include "SoC_EKF.h"
}


struct CellData{
	Vector_col x{};
	Matrix P{};
};


static std::array<CellData,135> soc_array{};


void vSOCManagerTask(void *argument)
{

	while(FullStackDataInstance::get().ltc_data.voltages.back() not_eq 0){
		osDelay(1000);
	}

	for(size_t i = 0; i < LtcConfig::CELL_COUNT; ++i){
		auto &cell_soc = soc_array[i];
		EKF_init(&cell_soc.x, &cell_soc.P);
		EKF_set_SoC_based_on_voltage(&cell_soc.x, FullStackDataInstance::get().ltc_data.voltages[i].load());
	}


	while(true)
	{
		osDelay(100);
		const float single_cell_current = FullStackDataInstance::get().external_data.acu_curr *  0.5f;

		for(size_t i = 0; i < LtcConfig::CELL_COUNT; ++i){
			auto &cell_soc = soc_array[i];
			const float cell_voltage = FullStackDataInstance::get().ltc_data.voltages[i];
			EKF_update(&cell_soc.x, &cell_soc.P, cell_voltage, single_cell_current, false);
			FullStackDataInstance::set().soc.cells_soc[i] = EKF_get_SoC(&cell_soc.x);
		}

	}
}
