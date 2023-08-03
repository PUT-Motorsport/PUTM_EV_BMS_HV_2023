/*
 * stackData.hpp
 *
 *  Created on: 20 lip 2023
 *      Author: piotr
 */

#ifndef STACKDATA_HPP_
#define STACKDATA_HPP_

#include <array.h>
#include <atomic>

constexpr static size_t bat_stack_size = 135;
// FIXME: do sprawdzenia ile temperatur
constexpr static size_t temp_stack_size = 65; // 3 * 5

class FullStackData
{
	struct LTCData
	{
		static std::array<std::atomic<float>, bat_stack_size> volt;
		static std::array<std::atomic<bool>, bat_stack_size> balance;
		static std::array<std::atomic<float>, temp_stack_size> temp;
		static float bat_volt;
	};
	struct ExternalData
	{
		static std::atomic<float> car_volt;
		static std::atomic<float> acu_volt;
		static std::atomic<float> acu_curr;
	};
	struct Other
	{
		static std::atomic<int> imd_state;
		//
	};
	struct Air
	{
		static std::atomic<bool> pre_state;
		static std::atomic<bool> p_state;
		static std::atomic<bool> m_state;
	};
};

inline FullStackData &get_FullStackData()
{
	static FullStackData FullStackData{};
	return FullStackData;
}

#endif /* STACKDATA_HPP_ */
