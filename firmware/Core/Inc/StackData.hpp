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

struct FullStackData
{
	struct LTCData
	{
		std::array<std::array<std::atomic<float>, 12>, chain_size > voltages;
		std::array<std::array<std::atomic<bool>, 12>, chain_size > discharge;
		std::array<std::array<std::atomic<float>, 5>, chain_size > temp;
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
