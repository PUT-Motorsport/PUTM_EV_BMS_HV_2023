/*
 * MCP356x.cpp
 *
 *  Created on: Jul 7, 2023
 *      Author: Piotr Lesicki
 */

#include <array>
#include <numeric>

#include <PerypherialManagers/Mcp356xController.hpp>
#include <PerypherialManagers/SpiDmaController.hpp>

using namespace Mcp356x;

Mcp356xController::Mcp356xController(GpioOut cs, SPI_HandleTypeDef &hspi, Mcp356xVersion version) : cs(cs), hspi(hspi), version(version)
{
	cs.deactivate();
}

template < WriteReadRegister Register >
void Mcp356xController::rawWrite(WCmd cmd, Register reg)
{
	cmd.value = cmd.value | address;
	std::array < uint8_t, 1 + sizeof(Register) > stxdata { 0 };
	std::array < uint8_t, 1 + sizeof(Register) > srxdata;

	stxdata[0] = cmd.value;
	serializeRegister(stxdata.begin() + 1, reg);

	SpiTxRxRequest request(cs, hspi, stxdata.begin(), srxdata.begin(), 1 + sizeof(Register));
	SpiDmaController::spiRequestAndWait(request);

	deserializeRegister(status_byte, srxdata.begin());
}

template < ReadRegister Register >
void Mcp356xController::rawRead(RCmd cmd, Register &reg)
{
	cmd.value = cmd.value | address;
	std::array < uint8_t, 1 + sizeof(Register) > stxdata { 0 };
	std::array < uint8_t, 1 + sizeof(Register) > srxdata;

	stxdata[0] = cmd.value;

	SpiTxRxRequest request(cs, hspi, stxdata.begin(), srxdata.begin(), 1 + sizeof(Register));
	SpiDmaController::spiRequestAndWait(request);

	deserializeRegister(status_byte, srxdata.begin());
	deserializeRegister(reg, srxdata.begin() + 1);
}

void Mcp356xController::readCfg(ConfigGroup &cfg)
{
	rawRead(Mcp356x::CMD_INC_READ(Mcp356x::Mcp356xRegisterAddress::CONFIG0), cfg);
}

void Mcp356xController::readMux(Mux &mux)
{
	rawRead(Mcp356x::CMD_INC_READ(Mcp356x::Mcp356xRegisterAddress::MUX), mux);
}

void Mcp356xController::readIrq(Irq &irq)
{
	rawRead(Mcp356x::CMD_INC_READ(Mcp356x::Mcp356xRegisterAddress::IRQ), irq);
}

void Mcp356xController::rawFast(FCmd cmd)
{
	cmd.value = cmd.value | address;
	uint8_t stxdata = 0;
	uint8_t srxdata;

	stxdata = cmd.value;

	SpiTxRxRequest request(cs, hspi, &stxdata, &srxdata, 1);
	SpiDmaController::spiRequestAndWait(request);

	deserializeRegister(status_byte, &srxdata);
}

bool Mcp356xController::statusByteOk()
{
	return status_byte.dev_addr0 xor status_byte.ndev_addr0;
}

StatusByte Mcp356xController::poolSatusByte()
{
	rawFast(CMD_POOL_STATUS);

	return status_byte;
}

void Mcp356xController::configure(ConfigGroup config)
{
	constexpr static std::array < double, 8 > gains { 1.0 / 3.0, 1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0 };
	adc_variant = config.data_format;
	size_t index = uint8_t(config.gain);
	gain = gains[index];
	rawFast(CMD_FULL_RESET);
	osDelay(10);
	rawWrite(CMD_INC_WRITE(Mcp356xRegisterAddress::CONFIG0), config);
	osDelay(100);
}

void Mcp356xController::setChannels(MuxIn channel_p, MuxIn channel_m)
{
	Mux selection =
	{
		.in_m = channel_m,
		.in_p = channel_p
	};
	rawWrite(CMD_INC_WRITE(Mcp356xRegisterAddress::MUX), selection);
}

void Mcp356xController::restartAdc()
{
	rawFast(CMD_ADC_RESTART);
}

bool Mcp356xController::dataReady()
{
	return not poolSatusByte().dr_status;
}

int32_t Mcp356xController::readData()
{
	int32_t result = 0;
	// the value is represent as if it was a signed int25 or int24
	// so we need to represent it as a signed int32
	switch (adc_variant)
	{
		case Mcp356x::DataFormat::_24bit :
		{
			AdcVariantAlignRight frame;
			rawRead(CMD_STATIC_READ(Mcp356xRegisterAddress::ADCDATA), frame);
//			adcRead(frame);
			uint32_t buff = uint32_t(frame.bytes[0]) << 16 | uint32_t(frame.bytes[1]) << 8 | uint32_t(frame.bytes[2]);
			if(frame.bytes[0] & 0x80) buff |= 0xff000000;
			result = int32_t(buff);
		} break;
		case Mcp356x::DataFormat::_24bit_left :
		{
			AdcVariantAlignLeft frame;
			rawRead(CMD_STATIC_READ(Mcp356xRegisterAddress::ADCDATA), frame);
//			adcRead(frame);
			uint32_t buff = uint32_t(frame.bytes[0]) << 16 | uint32_t(frame.bytes[1]) << 8 | uint32_t(frame.bytes[2]);
			if(frame.bytes[0] & 0x80) buff |= 0xff000000;
			result = int32_t(buff);
		} break;
		case Mcp356x::DataFormat::_24bit_right_sgn :
		{
			AdcVariantAlignRightSgn frame;
			rawRead(CMD_STATIC_READ(Mcp356xRegisterAddress::ADCDATA), frame);
//			adcRead(frame);
			uint32_t buff = uint32_t(frame.sgn) << 24 | uint32_t(frame.bytes[0]) << 16 | uint32_t(frame.bytes[1]) << 8 | uint32_t(frame.bytes[2]);
			result = int32_t(buff);
		} break;
		case Mcp356x::DataFormat::_24bit_right_sgn_id :
		{
			AdcVariantAlignRightSgnId frame;
			rawRead(CMD_STATIC_READ(Mcp356xRegisterAddress::ADCDATA), frame);
//			adcRead(frame);
			uint32_t buff = uint32_t(frame.bytes[0]) << 16 | uint32_t(frame.bytes[1]) << 8 | uint32_t(frame.bytes[2]);
			if(frame.sgn) buff |= 0xff000000;
			result = int32_t(buff);
		} break;
		default:
			break;
	}

	return result;
}

double Mcp356xController::readVoltage()
{
	return double(readData()) / 8'388'608.0 / gain + offset;
}
