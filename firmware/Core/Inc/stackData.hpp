/*
 * stackData.hpp
 *
 *  Created on: 20 lip 2023
 *      Author: piotr
 */

#ifndef STACKDATA_HPP_
#define STACKDATA_HPP_

#include <array>
#include <atomic>

constexpr static size_t bat_stack_size = 135;
constexpr static size_t temp_stack_size = 65; // 3 * 5 FIXME: do sprawdzenia ile temperatur

struct FullStackData
{
	struct LTCData
	{
		std::array<std::atomic<float>, bat_stack_size> volt;
		std::array<std::atomic<bool>, bat_stack_size> balance;
		std::array<std::atomic<float>, temp_stack_size> temp;
		std::atomic<float> min_temp;
		std::atomic<float> max_temp;
		std::atomic<float> bat_volt;
		std::atomic<float> soc;
	} ltcData;

	struct ExternalData
	{
		std::atomic<float> car_volt;
		std::atomic<float> acu_volt;
		std::atomic<float> acu_curr;
	} externalData;

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
};

class FullStackDataInstance
{
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
};

#endif /* STACKDATA_HPP_ */
