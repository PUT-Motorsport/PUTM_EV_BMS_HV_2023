/*
 * MCP356x.cpp
 *
 *  Created on: Jul 7, 2023
 *      Author: Piotr Lesicki
 */

#include <PerypherialManagers/MCP356Controller.hpp>

using namespace MCP356x;

MCP356Controller::MCP356Controller(GpioOut cs, SPI_HandleTypeDef &hspi, MCP356xVersion version) : cs(cs), hspi(hspi), version(version)
{
	cs.deactivate();
}

bool MCP356Controller::statusByteOk()
{
	return not status_byte.dr_status;
}

StatusByte MCP356Controller::poolSatusByte()
{
	uint8_t stxdata = prepCmd(MCP356xCommand::PoolStatus);
	uint8_t srxdata;

	SpiTxRxRequest request(cs, hspi, &stxdata, &srxdata, 1);
	SpiDmaController::spiRequestAndWait(request);

	deserializeReg(status_byte, 1, &srxdata);

	return status_byte;
}

uint8_t MCP356Controller::prepCmd(MCP356xCommand cmd)
{
	return uint8_t(this->address) | uint8_t(cmd);
}

uint8_t MCP356Controller::prepCmd(MCP356xRegisterAddress reg_addr, MCP356xCommandType type)
{
	return uint8_t(this->address) | uint8_t(reg_addr) | uint8_t(type);
}

void MCP356Controller::configure(Config config)
{
	//this->config = config;

	std::array < uint8_t, 5 > stxdata;
	std::array < uint8_t, 5 > srxdata;
	stxdata[0] = prepCmd(MCP356xRegisterAddress::CONFIG0, MCP356xCommandType::IncWrite);
	serializeReg(stxdata.begin() + 1, 1, config.config0);
	serializeReg(stxdata.begin() + 2, 1, config.config1);
	serializeReg(stxdata.begin() + 3, 1, config.config2);
	serializeReg(stxdata.begin() + 4, 1, config.config3);

	SpiTxRxRequest request(cs, hspi, stxdata.begin(), srxdata.begin(), 5);
	SpiDmaController::spiRequestAndWait(request);

	deserializeReg(status_byte, 1, stxdata.begin());
}

void setMeasurement(std::pair < MCP356x::MuxIn , MCP356x::MuxIn > channel_pair)
{
	Mux selection =
	{
		.in_m = uint8_t(channel_pair.first),
		.in_p = uint8_t(channel_pair.second)
	};

	uint8_t srxdata = 0;
	uint8_t stxdata = 0;
	serializeReg(&stxdata, 1, selection);
}

void MCP356Controller::request()
{
//	stxdata = prepCmd(MCP356xCommand::AdcRestart);
//	srxdata = 0;
//
//	request = SpiTxRxRequest(cs, hspi, &stxdata, &srxdata, 1);
//	SpiDmaController::spiRequestAndWait(request);
//
//	deserializeReg(status_byte, 1, &stxdata);
}

bool MCP356Controller::dataReady()
{
	return not (bool)poolSatusByte().dr_status;
}

uint32_t MCP356Controller::readData()
{
	std::array < uint8_t, 2 > stxdata;
	std::array < uint8_t, 2 > srxdata;
	stxdata[0] = prepCmd(MCP356xRegisterAddress::ADCDATA, MCP356xCommandType::StaticRead);
	stxdata[1] = 0;

	SpiTxRxRequest request(cs, hspi, stxdata.begin(), srxdata.begin(), 2);
	SpiDmaController::spiRequestAndWait(request);

	deserializeReg(status_byte, 1, stxdata.begin());

	return srxdata[1];
}
