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
class MCP356xController
{
	public:
		using Variant = MCP356x::AdcVariantAlignRightSgn;

		explicit MCP356xController(GpioOut cs, SPI_HandleTypeDef &hspi, MCP356xVersion version);

		constexpr static MCP356xAddress address = MCP356xAddress::_1;

		MCP356x::StatusByte status_byte;

		const GpioOut cs;

		const SPI_HandleTypeDef &hspi;

		MCP356xVersion version;

		template < MCP356x::WriteReadRegister Registers >
		void rawWrite(MCP356x::WCmd cmd, Registers regs);
		template < MCP356x::ReadRegister Register >
		void rawRead(MCP356x::RCmd cmd, Register &reg);
		void rawFast(MCP356x::FCmd cmd);

		MCP356x::StatusByte poolSatusByte();

		void configure(MCP356x::Config config);

		bool statusByteOk();
		void setChannels(std::pair < MCP356x::MuxIn , MCP356x::MuxIn > channel_pair);
		void restartAdc();
		bool dataReady();
		int32_t readData();

		//SpiDmaHandle prepReqPoolStatusByte();
	protected:
		MCP356x::Config config;

		//std::array < uint32_t*, 16 > binded_values;
};

#endif /* INC_PERYPHERIALMANAGERS_MCP356XCONTROLLER_HPP_ */
