/*
 * stackData.hpp
 *
 *  Created on: 20 lip 2023
 *      Author: piotr
 */

#ifndef STACKDATA_HPP_
#define STACKDATA_HPP_

#include "Config.hpp"
#include "Interfaces/StateErrorWarning.hpp"
#include <array>
#include <atomic>
#include "etl/flat_map.h"

struct FullStackData
{
	struct LTCData
	{
		std::array<std::atomic<float>, LtcConfig::CELL_COUNT> voltages;
		std::array<std::atomic<bool>, LtcConfig::CELL_COUNT> discharge{false};
		std::array<std::atomic<float>, LtcConfig::TEMP_COUNT> temp;
		std::array<std::atomic<float>, LtcConfig::TEMP_COUNT> temp_C;
		std::atomic<float> min_temp;
		std::atomic<float> max_temp;
		std::atomic<float> bat_volt;
		std::atomic<float> soc;
		std::atomic<bool> charger_connected{true};
	} ltc_data;

	struct ExternalData
	{
		std::atomic<float> car_volt;
		std::atomic<float> acu_volt;
		std::atomic<float> acu_curr;
		std::atomic<bool> safety_state{false};
	} external_data;

	struct Other
	{
		std::atomic<int> imd_state;
	} other;

	struct Air_detect
	{
		std::atomic<bool> pre_state{false};
		std::atomic<bool> p_state{false};
		std::atomic<bool> m_state{false};
	} air_detect;

	struct State
	{
		std::atomic<bool> ts_activation_button{false};
		std::optional<Checks::CriticalError> error{std::nullopt};
	} state;

	struct ChargeBalance
	{
		std::atomic<float> max_cell_voltage{4.15f};
		std::atomic<float> min_cell_voltage{3.0f};
		std::atomic<float> avg_cell_voltage{0.0f};
		std::atomic<float> median_cell_voltage{0.0f};
		std::atomic<float> std_dev_cell_voltage{0.0f};
		std::atomic<float> voltage_sum{0.0f};
		std::array<std::atomic<float>, LtcConfig::CELL_COUNT> pre_balance_voltages;
	} charge_balance;

	struct SoC
	{
		std::array<std::atomic<float>, LtcConfig::CELL_COUNT> cells_soc;
	} soc;

	struct Charger
	{
		std::atomic<bool> charged_detected;
		// set by USB
		std::atomic<bool> balance_enable{false};
		std::atomic<uint32_t> balance_disable_tick{};
		std::atomic<bool> charging_enable{false};
		std::atomic<float> charge_current{0.0f};
	} charger;

	struct UsbEvents
	{
		std::atomic<bool> discharge_optical_visualisation{false};
	} usb_events;

	struct Time{
		std::atomic<uint32_t> tick;
	} time;

	FullStackData() = default;
	FullStackData(const FullStackData &) = delete;
	FullStackData &operator=(const FullStackData &) = delete;
};

class FullStackDataInstance
{
public:
	inline static FullStackData &set()
	{
		static FullStackData instance;
		return instance;
	}

	inline static const FullStackData &get()
	{
		return set();
	}
};

#endif /* STACKDATA_HPP_ */
