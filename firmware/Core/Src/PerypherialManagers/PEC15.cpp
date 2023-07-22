/*
 * PEC15.cpp
 *
 *  Created on: Jul 20, 2023
 *      Author: piotr
 */

#include "PerypherialManagers/PEC15.hpp"

std::array < uint8_t, 2 > calcPEC (uint8_t const *begin, uint8_t const *end)
{
	uint16_t remainder;
	uint16_t address;
	remainder = 16;
	for(auto d = begin; d != end; d++)
	{
		address = ((remainder >> 7) ^ *d) & 0xff;
		remainder = (remainder << 8 ) ^ pec_table[address];
	}
	remainder *= 2;
	return { uint8_t(remainder >> 8) , uint8_t(remainder) } ;
}
