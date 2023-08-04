/*
 * CarCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: jan
 */

#define PUTM_USE_CAN_FD
#include "PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp"
#include "PerypherialManagers/CanUtils.hpp"
#include "app_freertos.h"
#include "fdcan.h"
#include "main.h"
#include <algorithm>
#include <StackData.hpp>

static FDCAN_HandleTypeDef &hfdcan = hfdcan3;

auto voltages_message(size_t &cell_index)
{
	const FullStackData &fsd = FullStackDataInstance::get();

	auto voltage_to_can = [](float voltage) -> uint16_t
	{
		return static_cast<uint16_t>(voltage * 1'000 - 2'850);
	};

	auto clmp = [&](size_t index) -> size_t {
		return std::clamp(index, (size_t)0, (size_t)fsd.ltcData.volt.size() -1);
	};

	const PUTM_CAN::BMS_HV_cell_voltages frame = {
		.cell_start = static_cast<uint8_t>(clmp(cell_index)),
		.v_cell_start = voltage_to_can(fsd.ltcData.volt.at(clmp(cell_index))),
		.v_cell_start_plus_1 = voltage_to_can(fsd.ltcData.volt.at(clmp(cell_index + 1))),
		.v_cell_start_plus_2 = voltage_to_can(fsd.ltcData.volt.at(clmp(cell_index + 2))),
		.v_cell_start_plus_3 = voltage_to_can(fsd.ltcData.volt.at(clmp(cell_index + 3))),
		.cell_end = static_cast<uint8_t>(clmp(cell_index + 3))};

	// FIXME
	if (cell_index + 4 < fsd.ltcData.volt.size())
	{
		cell_index = cell_index + 4;
	}
	else
	{
		cell_index = 0;
	}

	return PUTM_CAN::Can_tx_message(frame, PUTM_CAN::can_tx_header_BMS_HV_cell_voltages);
}

void vCarCANManagerTask(void *argument)
{
	size_t cell_send_index{0};
	startCan(hfdcan);
	while (true)
	{
		osDelay(10);
		while (get_can_fifo_message_count(hfdcan))
		{
			PUTM_CAN::can.parse_message(PUTM_CAN::Can_rx_message(hfdcan));
		}

		const FullStackData &fsd = FullStackDataInstance::get();

		PUTM_CAN::BMS_HV_main main_frame = {
			.voltage_sum = static_cast<uint16_t>(fsd.ltcData.bat_volt),
			.current = static_cast<int16_t>(fsd.externalData.acu_curr * 100.0f),
			.temp_max = static_cast<uint8_t>(fsd.ltcData.max_temp),
			.temp_avg = static_cast<uint8_t>(fsd.ltcData.min_temp),
			.soc = static_cast<uint16_t>(fsd.ltcData.soc * 1000)};

		auto status = PUTM_CAN::Can_tx_message(main_frame, PUTM_CAN::can_tx_header_BMS_HV_MAIN).send(hfdcan);

		auto status_2 = voltages_message(cell_send_index).send(hfdcan);

		if (status not_eq HAL_OK or status_2 not_eq HAL_OK)
		{
			// Error_Handler();
		}
	}
}
