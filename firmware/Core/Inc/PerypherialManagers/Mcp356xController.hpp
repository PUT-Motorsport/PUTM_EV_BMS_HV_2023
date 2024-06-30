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

enum struct Mcp356xVersion
{
	MCP3561,
	MCP3562
};

enum struct Mcp356xAddress : uint8_t
{
	_0 = 0b00'000000,
	_1 = 0b01'000000,
	_2 = 0b10'000000,
	_3 = 0b11'000000,
};

class Mcp356xController
{
	public:
		explicit Mcp356xController(GpioOut cs, SPI_HandleTypeDef &hspi);

		constexpr static Mcp356xAddress address = Mcp356xAddress::_1;

		Mcp356x::StatusByte status_byte;

		GpioOut cs;

		const SPI_HandleTypeDef &hspi;

		Mcp356xVersion version;

		template < Mcp356x::WriteReadRegister Registers >
		void rawWrite(Mcp356x::WCmd cmd, Registers regs);
		template < Mcp356x::ReadRegister Register >
		void rawRead(Mcp356x::RCmd cmd, Register &reg);
		void rawFast(Mcp356x::FCmd cmd);
		void readCfg(Mcp356x::ConfigGroup &cfg);
		void readMux(Mcp356x::Mux &mux);
		void readIrq(Mcp356x::Irq &irq);

		Mcp356x::StatusByte poolSatusByte();

		void configure(Mcp356x::ConfigGroup config);
		void init();

		bool statusByteOk();
		void setChannels(Mcp356x::MuxIn ch_p, Mcp356x::MuxIn ch_m);
		void restartAdc();
		bool dataReady();
		int32_t readData();
		float readVoltage();

		float gain { 1.f };
		float offset { 0.f };
	protected:
	private:
		Mcp356x::DataFormat adc_variant;
};

#endif /* INC_PERYPHERIALMANAGERS_MCP356XCONTROLLER_HPP_ */
