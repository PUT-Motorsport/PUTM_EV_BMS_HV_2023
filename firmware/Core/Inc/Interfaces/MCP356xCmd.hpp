/*
 * MCP356xCmd.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: piotr
 */

#ifndef INC_PERYPHERIALMANAGERS_MCP356XCMD_HPP_
#define INC_PERYPHERIALMANAGERS_MCP356XCMD_HPP_

#include <main.h>
#include <concepts>

#include <Utils/Utils.hpp>

namespace Mcp356x
{
	enum struct Mcp356xRegisterAddress : uint8_t
	{
		ADCDATA = 	0b00'0000'00,
		CONFIG0 = 	0b00'0001'00,
		CONFIG1 = 	0b00'0010'00,
		CONFIG2 = 	0b00'0011'00,
		CONFIG3 = 	0b00'0100'00,
		IRQ = 		0b00'0101'00,
		MUX = 		0b00'0110'00,
		SCAN = 		0b00'0111'00,
		TIMER = 	0b00'1000'00,
		OFFSETCAL = 0b00'1001'00,
		GAINCAL = 	0b00'1010'00,
		RESERVED1 = 0b00'1011'00,
		RESERVED2 = 0b00'1100'00,
		LOCK = 		0b00'1101'00,
		RESERVED3 = 0b00'1110'00,
		CRCCFG = 	0b00'1111'00,
	};

	struct RCmd
	{
		uint8_t value;
	};
	struct WCmd
	{
		uint8_t value;
	};
	struct FCmd
	{
		uint8_t value;
	};

	constexpr FCmd CMD_POOL_STATUS 		{ 0b00'0000'00 };
	constexpr FCmd CMD_ADC_RESTART 		{ 0b00'1010'00 };
	constexpr FCmd CMD_ADC_STANDBY 		{ 0b00'1011'00 };
	constexpr FCmd CMD_ADC_SHUTDOWN 	{ 0b00'1100'00 };
	constexpr FCmd CMD_FULL_SHUTDOWN	{ 0b00'1101'00 };
	constexpr FCmd CMD_FULL_RESET 		{ 0b00'1110'00 };

	static constexpr RCmd CMD_STATIC_READ(Mcp356xRegisterAddress addr)
	{
		return RCmd { 0b000000'01 | addr };
	}
	constexpr RCmd CMD_INC_READ(Mcp356xRegisterAddress addr)
	{
		return RCmd { 0b000000'11 | addr }; //IncrementalRead
	}
	static constexpr WCmd CMD_INC_WRITE(Mcp356xRegisterAddress addr)
	{
		return WCmd { 0b000000'10 | addr }; //IncrementalWrite
	}
}

#endif /* INC_PERYPHERIALMANAGERS_MCP356XCMD_HPP_ */
