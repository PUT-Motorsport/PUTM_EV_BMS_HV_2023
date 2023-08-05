/*
 * MCP356x.cpp
 *
 *  Created on: Jul 7, 2023
 *      Author: Piotr Lesicki
 */

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
	serializeRegister(stxdata.begin(), reg);

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
	rawFast(CMD_FULL_RESET);
	rawWrite(CMD_INC_WRITE(Mcp356xRegisterAddress::CONFIG0), config);
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
	return not (bool)poolSatusByte().dr_status;
}

int32_t Mcp356xController::readData()
{
	return readDataVariant< Mcp356xConfig::ADC_VARIANT >();
}

template < Mcp356x::AdcVariant Variant >
inline int32_t Mcp356xController::readDataVariant()
{
	return 0;
}

template <>
inline int32_t Mcp356xController::readDataVariant< AdcVariantAlignRight >()
{
	// the value is represent as if it was a signed int25 or int24
	// so we need to represent it as a signed int32

	int32_t result = 0;
	AdcVariantAlignRight frame;
	rawRead(CMD_STATIC_READ(Mcp356xRegisterAddress::ADCDATA), frame);
	if(frame.sgn) result = 0xff'80'00'00 | frame.value;
	else result = frame.value;
	return result;
}

template <>
inline int32_t Mcp356xController::readDataVariant< AdcVariantAlignLeft >()
{
	// the value is represent as if it was a signed int25 or int24
	// so we need to represent it as a signed int32

	int32_t result = 0;
	AdcVariantAlignLeft frame;
	rawRead(CMD_STATIC_READ(Mcp356xRegisterAddress::ADCDATA), frame);
	if(frame.sgn) result = 0xff'80'00'00 | frame.value;
	else result = frame.value;
	return result;
}

template <>
inline int32_t Mcp356xController::readDataVariant< AdcVariantAlignRightSgn >()
{
	// the value is represent as if it was a signed int25 or int24
	// so we need to represent it as a signed int32

	int32_t result = 0;
	AdcVariantAlignRightSgn frame;
	rawRead(CMD_STATIC_READ(Mcp356xRegisterAddress::ADCDATA), frame);
	if(frame.sgn) result = 0xff'00'00'00 | frame.value;
	else result = frame.value;
	return result;
}

//template <>
//class MCP356xController<MCP356x::AdcVariantAlignLeft>;

//template <>
//class MCP356xController<MCP356x::AdcVariantAlignRight>;

//template <>
//class MCP356xController<MCP356x::AdcVariantAlignRightSgn>;

//template <>
//class MCP356xController<MCP356x::AdcVariantAlignRightSgnId>;
