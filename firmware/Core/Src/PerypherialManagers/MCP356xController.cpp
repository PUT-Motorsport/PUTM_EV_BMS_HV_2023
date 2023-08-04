/*
 * MCP356x.cpp
 *
 *  Created on: Jul 7, 2023
 *      Author: Piotr Lesicki
 */

#include <PerypherialManagers/MCP356xController.hpp>

using namespace MCP356x;

//template < AdcVariant Variant >
MCP356xController::MCP356xController(GpioOut cs, SPI_HandleTypeDef &hspi, MCP356xVersion version) : cs(cs), hspi(hspi), version(version)
{
	cs.deactivate();
}

//template < AdcVariant Variant >
template < WriteReadRegister Register >
void MCP356xController::rawWrite(WCmd cmd, Register reg)
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

//template < AdcVariant Variant >
template < ReadRegister Register >
void MCP356xController::rawRead(RCmd cmd, Register &reg)
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

//template < AdcVariant Variant >
void MCP356xController::rawFast(FCmd cmd)
{
	cmd.value = cmd.value | address;
	uint8_t stxdata = 0;
	uint8_t srxdata;

	stxdata = cmd.value;

	SpiTxRxRequest request(cs, hspi, &stxdata, &srxdata, 1);
	SpiDmaController::spiRequestAndWait(request);

	deserializeRegister(status_byte, &srxdata);
}

//template < AdcVariant Variant >
bool MCP356xController::statusByteOk()
{
	return status_byte.dev_addr0 xor status_byte.ndev_addr0;
}

//template < AdcVariant Variant >
StatusByte MCP356xController::poolSatusByte()
{
	rawFast(CMD_POOL_STATUS);

	return status_byte;
}

//template < AdcVariant Variant >
void MCP356xController::configure(Config config)
{
	rawWrite(CMD_INC_WRITE(MCP356xRegisterAddress::CONFIG0), config.config0);
	rawWrite(CMD_INC_WRITE(MCP356xRegisterAddress::CONFIG1), config.config1);
	rawWrite(CMD_INC_WRITE(MCP356xRegisterAddress::CONFIG2), config.config2);
	rawWrite(CMD_INC_WRITE(MCP356xRegisterAddress::CONFIG3), config.config3);
}

//template < AdcVariant Variant >
void MCP356xController::setChannels(std::pair < MCP356x::MuxIn , MCP356x::MuxIn > channel_pair)
{
	Mux selection =
	{
		.in_m = uint8_t(channel_pair.first),
		.in_p = uint8_t(channel_pair.second)
	};

	rawWrite(CMD_INC_WRITE(MCP356xRegisterAddress::MUX), selection);
}

//template < AdcVariant Variant >
void MCP356xController::restartAdc()
{
	rawFast(CMD_ADC_RESTART);
}

//template < AdcVariant Variant >
bool MCP356xController::dataReady()
{
	return not (bool)poolSatusByte().dr_status;
}

//template < AdcVariant Variant >
int32_t MCP356xController::readData()
{
	int32_t result = 0;
	if constexpr (std::same_as< Variant, AdcVariantAlignRight >)
	{
		AdcVariantAlignRight frame;
		rawRead(CMD_STATIC_READ(MCP356xRegisterAddress::ADCDATA), frame);
		result = frame.value;
	}
	else if constexpr (std::same_as< Variant, AdcVariantAlignLeft >)
	{
		AdcVariantAlignLeft frame;
		rawRead(CMD_STATIC_READ(MCP356xRegisterAddress::ADCDATA), frame);
		result = frame.value;
	}
	else if constexpr (std::same_as< Variant, AdcVariantAlignRightSgn >)
	{
		AdcVariantAlignRightSgn frame;
		rawRead(CMD_STATIC_READ(MCP356xRegisterAddress::ADCDATA), frame);
		// the value is represent as if it was a signed int25
		// so we need to represent it as a signed int32
		if(frame.sgn) result = 0xff'00'00'00 | frame.value;
		else result = frame.value;
	}
	return 0;
}

//template <>
//class MCP356xController<MCP356x::AdcVariantAlignLeft>;

//template <>
//class MCP356xController<MCP356x::AdcVariantAlignRight>;

//template <>
//class MCP356xController<MCP356x::AdcVariantAlignRightSgn>;

//template <>
//class MCP356xController<MCP356x::AdcVariantAlignRightSgnId>;
