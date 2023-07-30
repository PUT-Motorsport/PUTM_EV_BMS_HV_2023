/*
 * MCP3561.hpp
 *
 *  Created on: Jul 6, 2023
 *      Author: piotr
 */

#ifndef INC_PERYPHERIALMANAGERS_MCP356X_HPP_
#define INC_PERYPHERIALMANAGERS_MCP356X_HPP_

#include <PerypherialManagers/SpiDmaController.hpp>
#include "Gpio.hpp"
#include "PerypherialManagers/LocableResource.hpp"

enum struct MCP356xVersion
{
	MCP3561,
	MCP3562
};

enum struct MCP356xAddress : uint8_t
{
	_0 = 0b00'000000,
	_1 = 0b01'000000,
	_2 = 0b10'000000,
	_3 = 0b11'000000,
};

enum struct MCP356xCommandType : uint8_t
{
	//Fast = 				0b000000'00,
	StaticRead = 	0b000000'01,
	IncWrite = 		0b000000'10, 	//IncrementalWrite
	IncRead = 		0b000000'11 	//IncrementalRead
};

enum struct MCP356xCommand : uint8_t
{
	PoolStatus = 	0b00'0000'00,
	AdcRestart = 	0b00'1010'00,
	AdcStandby = 	0b00'1011'00,
	AdcShutdown = 	0b00'1100'00,
	FullShutdown = 	0b00'1101'00,
	FullReset = 	0b00'1110'00
};

enum struct MCP356xRegisterAddress : uint8_t
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

class MCP3561x
{
	public:
		explicit MCP3561x(GpioOut cs, SPI_HandleTypeDef &hspi, MCP356xVersion version);

		MCP356xAddress address = MCP356xAddress::_1;

		MCP356xVersion version;

		uint8_t status_byte;

		SPI_HandleTypeDef &hspi;

		GpioOut cs;

		bool statusByteOk();

		uint8_t prepCmd(MCP356xCommand cmd);
		uint8_t prepCmd(MCP356xRegisterAddress reg_addr, MCP356xCommandType type);

		void poolSatusByte();

		//SpiDmaHandle prepReqPoolStatusByte();
	protected:
};

#endif /* INC_PERYPHERIALMANAGERS_MCP356X_HPP_ */
