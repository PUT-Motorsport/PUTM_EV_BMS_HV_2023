/*
 * MCP3561.hpp
 *
 *  Created on: Jul 6, 2023
 *      Author: piotr
 */

#ifndef INC_PERYPHERIALMANAGERS_MCP356XCONTROLLER_HPP_
#define INC_PERYPHERIALMANAGERS_MCP356XCONTROLLER_HPP_

#include <main.h>
#include <array>

#include <PerypherialManagers/GpioController.hpp>
#include <Interfaces/MCP356xCmd.hpp>
#include <Interfaces/MCP356xRegs.hpp>
#include <Config.hpp>

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

//template < MCP356x::AdcVariant Variant >
class Mcp356xController
{
	public:
		explicit Mcp356xController(GpioOut cs, SPI_HandleTypeDef &hspi, MCP356xVersion version);

		constexpr static MCP356xAddress address = MCP356xAddress::_1;

		Mcp356x::StatusByte status_byte;

		const GpioOut cs;

		const SPI_HandleTypeDef &hspi;

		MCP356xVersion version;

		template < Mcp356x::WriteReadRegister Registers >
		void rawWrite(Mcp356x::WCmd cmd, Registers regs);
		template < Mcp356x::ReadRegister Register >
		void rawRead(Mcp356x::RCmd cmd, Register &reg);
		void rawFast(Mcp356x::FCmd cmd);

		Mcp356x::StatusByte poolSatusByte();

		void configure(Mcp356x::Config config);

		bool statusByteOk();
		void setChannels(std::pair < Mcp356x::MuxIn , Mcp356x::MuxIn > channel_pair);
		void restartAdc();
		bool dataReady();
		//template < MCP356x::AdcVariant Variant >
		int32_t readData();

		//SpiDmaHandle prepReqPoolStatusByte();
	protected:
		Mcp356x::Config config;

		template < Mcp356x::AdcVariant Variant >
		inline int32_t readDataVariant();

		//std::array < uint32_t*, 16 > binded_values;
};

template <>
inline int32_t Mcp356xController::readDataVariant< Mcp356x::AdcVariantAlignLeft >();

template <>
inline int32_t Mcp356xController::readDataVariant< Mcp356x::AdcVariantAlignRight >();

template <>
inline int32_t Mcp356xController::readDataVariant< Mcp356x::AdcVariantAlignRightSgn >();

#endif /* INC_PERYPHERIALMANAGERS_MCP356XCONTROLLER_HPP_ */
