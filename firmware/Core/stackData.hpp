/*
 * stackData.hpp
 *
 *  Created on: 20 lip 2023
 *      Author: piotr
 */

#ifndef STACKDATA_HPP_
#define STACKDATA_HPP_

#include <array.h>

constexpr static size_t bat_stack_size = 135;
//FIXME: do sprawdzenia ile temperatur
constexpr static size_t temp_stack_size = 65; // 3 * 5

class FullStackData
{
	struct LTCData
	{
		static std::array < float, bat_stack_size > volt;
		static std::array < float, temp_stack_size > temp;
		static float bat_volt;
	};
	struct ExternalData
	{
		static float car_volt;
		static float acu_volt;
		static float acu_curr;
	};
	struct Other
	{
		static float imd_state;
		//
	};
	struct Air
	{
		static bool pre_state;
		static bool p_state;
		static bool m_state;
	};
};

#endif /* STACKDATA_HPP_ */
