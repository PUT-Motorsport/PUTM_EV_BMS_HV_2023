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

struct FullStackData
{
	struct LTCData
	{
		std::array<std::atomic<float>, LtcConfig::CELL_COUNT> voltages;
		std::array<std::atomic<bool>, LtcConfig::CELL_COUNT> discharge { false };
		std::array<std::atomic<float>, LtcConfig::TEMP_COUNT> temp;
		//std::array<std::atomic<uint16_t> temp_count>
		std::atomic<float> min_temp;
		std::atomic<float> max_temp;
		std::atomic<float> bat_volt;
		std::atomic<float> soc;
		std::atomic<bool> charger_connected{false};
	} ltc_data;

	struct ExternalData
	{
		std::atomic<float> car_volt;
		std::atomic<float> acu_volt;
		std::atomic<float> acu_curr;
	} external_data;

	struct Other
	{
		std::atomic<int> imd_state;
	} other;

	struct Air
	{
		std::atomic<bool> pre_state;
		std::atomic<bool> p_state;
		std::atomic<bool> m_state;
	} air;

	struct State
	{
		std::optional<Checks::CriticalError> error{std::nullopt};
		std::optional<Checks::Warning> warning{std::nullopt};
	} state;

	struct ChargeBalance
	{
		std::atomic<bool> balance_enable { false };
		std::atomic<float> max_cell_voltage { 4.15f };
		std::atomic<float> min_cell_voltage { 3.0f };
		std::atomic<float> avg_cell_voltage { 0.0f };
		std::atomic<float> std_dev_cell_voltage { 0.0f };
	} charge_balance;

	constexpr FullStackData() = default;
	FullStackData(const FullStackData &) = delete;
	FullStackData &operator=(const FullStackData &) = delete;
};

class FullStackDataInstance
{
public:
	static FullStackData &getAndModify()
	{
		static FullStackData instance;
		return instance;
	}

	static const FullStackData &get()
	{
		return getAndModify();
	}
};

#endif /* STACKDATA_HPP_ */
