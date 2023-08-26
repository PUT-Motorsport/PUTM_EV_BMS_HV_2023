/*
 * CarCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: jan
 */
#include <algorithm>
#include <fdcan.h>
#include <main.h>

#include <PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp>
#include <StackData.hpp>
#include <Utils/CanUtils.hpp>
#include <app_freertos.h>

static FDCAN_HandleTypeDef &hfdcan = hfdcan3;

auto voltages_message(size_t &cell_index)
{
	const FullStackData &fsd = FullStackDataInstance::get();

	auto voltage_to_can = [](float voltage) -> uint16_t
	{
		return static_cast<uint16_t>(voltage * 1'000 - 2'850);
	};

	auto clmp = [&](size_t index) -> size_t
	{
		return std::clamp(index, (size_t)0, (size_t)fsd.ltc_data.voltages.size() - 1);
	};

	const PUTM_CAN::BMS_HV_cell_voltages frame = {
		.cell_start = static_cast<uint8_t>(clmp(cell_index)),
		.v_cell_start = voltage_to_can(fsd.ltc_data.voltages.at(clmp(cell_index))),
		.v_cell_start_plus_1 = voltage_to_can(fsd.ltc_data.voltages.at(clmp(cell_index + 1))),
		.v_cell_start_plus_2 = voltage_to_can(fsd.ltc_data.voltages.at(clmp(cell_index + 2))),
		.v_cell_start_plus_3 = voltage_to_can(fsd.ltc_data.voltages.at(clmp(cell_index + 3))),
		.cell_end = static_cast<uint8_t>(clmp(cell_index + 3))};

	// FIXME
	if (cell_index + 4 < fsd.ltc_data.voltages.size())
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

	uint32_t send_tick{0};

	while (true)
	{
		osDelay(10);
		while (getCanFifoMessageCount(hfdcan3))
		{
			PUTM_CAN::can.parse_message(PUTM_CAN::Can_rx_message(hfdcan));
		}

		if (PUTM_CAN::can.get_aq_ts_button_new_data())
		{
			FullStackDataInstance::set().state.ts_activation_button = true;
		}

		const FullStackData &fsd = FullStackDataInstance::get();

		PUTM_CAN::BMS_HV_main main_frame = {
			.voltage_sum = static_cast<uint16_t>(fsd.charge_balance.voltage_sum * 100.0f),
			.current = static_cast<int16_t>(fsd.external_data.acu_curr * 100.0f),
			.temp_max = static_cast<uint8_t>(fsd.ltc_data.max_temp),
			.temp_avg = static_cast<uint8_t>(fsd.ltc_data.min_temp),
			.soc = static_cast<uint16_t>(fsd.soc.cells_soc.front() * 1'000)};

		auto status = PUTM_CAN::Can_tx_message(main_frame, PUTM_CAN::can_tx_header_BMS_HV_MAIN).send(hfdcan);

		auto status_2 = voltages_message(cell_send_index).send(hfdcan);

		if (status not_eq HAL_OK or status_2 not_eq HAL_OK)
		{
			// Error_Handler();
		}
	}
}
