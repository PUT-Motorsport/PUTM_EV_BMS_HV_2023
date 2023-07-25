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
//FIXME: not sure if remainder should be shifted to left by 1 cuz
//algorithm gives a 15bit valuea and it should be send in the
//[16:0] = { 15..0 0 } som im not sure if the provided by the doc
//code takes it into account
#warning "not sure if remainder should be shifted to left by 1"
	return { uint8_t(remainder >> 8), uint8_t(remainder) } ;
}
