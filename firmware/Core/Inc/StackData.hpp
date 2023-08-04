/*
 * stackData.hpp
 *
 *  Created on: 20 lip 2023
 *      Author: piotr
 */

#ifndef STACKDATA_HPP_
#define STACKDATA_HPP_

#include "Interfaces/StateErrorWarning.hpp"
#include <array>
#include <atomic>
<<<<<<< HEAD:firmware/Core/Inc/stackData.hpp

constexpr static size_t bat_stack_size = 135;
constexpr static size_t temp_stack_size = 65; // 3 * 5 FIXME: check temp sensor count
=======
#include "Config.hpp"
>>>>>>> main:firmware/Core/Inc/StackData.hpp

struct FullStackData
{
	struct LTCData
	{
		std::array<std::atomic<float>, cell_count> voltages;
		std::array<std::atomic<bool>, cell_count> discharge;
		std::array<std::atomic<float>, temp_count> temp;
		std::atomic<float> min_temp;
		std::atomic<float> max_temp;
		std::atomic<float> bat_volt;
		std::atomic<float> soc;
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
		std::optional<CHECKS::CriticalError> error{std::nullopt};
		std::optional<CHECKS::Warning> warning{std::nullopt};
	} state;

	constexpr FullStackData() = default;
	FullStackData(const FullStackData &) = delete;
	FullStackData &operator=(const FullStackData &) = delete;
};

class FullStackDataInstance
{
<<<<<<< HEAD:firmware/Core/Inc/stackData.hpp
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
=======
	public:
		static FullStackData &get()
		{
			static FullStackData instance{};
			return instance;
		}

		static const FullStackData &getConst()
		{
			return get();
		}
>>>>>>> main:firmware/Core/Inc/StackData.hpp
};

#endif /* STACKDATA_HPP_ */
