/*
 * MCP356x.cpp
 *
 *  Created on: Jul 7, 2023
 *      Author: Piotr Lesicki
 */

#include "PerypherialManagers/MCP356x.hpp"

MCP3561x::MCP3561x(GpioOut cs, SPI_HandleTypeDef &hspi, MCP356xVersion version) : cs(cs), hspi(hspi), version(version)
{
	cs.deactivate();
}

bool MCP3561x::statusByteOk()
{
	return ((status_byte & 0b01000000) >> 1) ^ (status_byte & 0b001000000);
}

void MCP3561x::poolSatusByte()
{
	uint8_t tx_buff = prepCmd(MCP356xCommand::PoolStatus);
	uint8_t rx_buff;

	SpiTxRxRequest request(cs, hspi, &tx_buff, &rx_buff, 1);
	SpiDmaController::spiRequestAndWait(request);

	status_byte = rx_buff;
}

uint8_t MCP3561x::prepCmd(MCP356xCommand cmd)
{
	return uint8_t(this->address) | uint8_t(cmd);
}

uint8_t MCP3561x::prepCmd(MCP356xRegisterAddress reg_addr, MCP356xCommandType type)
{
	return uint8_t(this->address) | uint8_t(reg_addr) | uint8_t(type);
}
