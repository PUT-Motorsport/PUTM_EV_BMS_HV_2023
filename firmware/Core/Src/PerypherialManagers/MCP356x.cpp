/*
 * MCP356x.cpp
 *
 *  Created on: Jul 7, 2023
 *      Author: Piotr Lesicki
 */

#include "PerypherialManagers/MCP356x.hpp"

MCP3561x::MCP3561x(GpioOut cs, SPI_HandleTypeDef *hspi, MCP356xVersion version) : cs(cs), hspi(hspi), version(version)
{
	//cs.lock();
	cs.deactivate();
	//cs.unlock();
}

bool MCP3561x::statusByteOk()
{
	return ((status_byte & 0b01000000) >> 1) ^ (status_byte & 0b001000000);
}

void MCP3561x::poolSatusByte()
{
	//tx_buffer[0] = prepCmd(MCP356xCommand::PoolStatus);
	uint8_t tx_buff = prepCmd(MCP356xCommand::PoolStatus);
	uint8_t rx_buff;

	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = &this->cs,
		.hspi = this->hspi,
		.pTxData = &tx_buff,
		.pRxData = &rx_buff,
		.dataSize = 1
	};

	SpiDmaController::spiRequestAndWait(temp);

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
