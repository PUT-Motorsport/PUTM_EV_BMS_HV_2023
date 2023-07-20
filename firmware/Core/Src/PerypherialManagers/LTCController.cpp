/*
 * LTCController.cpp
 *
 *  Created on: 19 lip 2023
 *      Author: piotr
 */

#include "PerypherialManagers/LTCController.hpp"
#include "PerypherialManagers/SpiDmaManager.hpp"
#include "PerypherialManagers/LTC6811CmdCodes.hpp"
#include "task.h"

LTCController::LTCController(GpioOut gpio, SPI_HandleTypeDef* hspi) : hspi(hspi), gpio(gpio)
{
	gpio.deactivate();
}

void LTCController::wakeUp()
{
	uint8_t dummy_cmd = 0;
	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = &this->gpio,
		.hspi = this->hspi,
		.pTxData = &dummy_cmd,
		.pRxData = nullptr,
		.dataSize = 1,
	};

	SpiDmaManager::spiRequestAndWait(temp);
	osDelay(Config::twake_full);
	SpiDmaManager::spiRequestAndWait(temp);
	osDelay(Config::twake_full);
}

void LTCController::handleWatchDog()
{
	//TODO: also some dummy rdcnfg?

	uint8_t dummy_cmd = 0;
	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = &this->gpio,
		.hspi = this->hspi,
		.pTxData = &dummy_cmd,
		.pRxData = nullptr,
		.dataSize = 1,
	};

	SpiDmaManager::spiRequestAndWait(temp);
	osDelay(Config::twake_full);
}

template < class WrRdReg >
HAL_StatusTypeDef LTCController::rawWrite(WCmd cmd, std::array< WrRdReg, chain_size > const &data)
{
	HAL_StatusTypeDef status = HAL_OK;

	std::array < uint8_t, 2 > scmd = serializeCmd(cmd);
	std::array < uint8_t, 2 > scmd_pec = calcPEC(scmd.begin(), scmd.end());

	std::array < uint8_t, chain_size * 8 + 4 > stxdata;
	auto stdit = stxdata.begin();
	std::copy(scmd.begin(), scmd.end(), stdit);
	stdit += 2;
	std::copy(scmd_pec.begin(), scmd_pec.end(), stdit);
	stdit += 2;

	for(auto dit = data.rbegin(); dit != data.rend(); dit++)
	{
		auto sd = serializeRegisterGroup(*dit);
		auto sd_pec = calcPEC(sd);
		std::copy(sd.begin(), sd.end(), stdit);
		std::copy(sd_pec.begin(), sd_pec.end(), stdit);
		stdit += 8;
	}

	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = &this->gpio,
		.hspi = this->hspi,
		.pTxData = stxdata.begin(),
		.pRxData = nullptr,
		.dataSize = stxdata.size(),
	};

	SpiDmaManager::spiRequestAndWait(temp);

	return status;
}

HAL_StatusTypeDef LTCController::rawWrite(WCmd cmd)
{
	HAL_StatusTypeDef status = HAL_OK;

	std::array < uint8_t, 2 > scmd = serializeCmd(cmd);
	std::array < uint8_t, 2 > scmd_pec = calcPEC(scmd.begin(), scmd.end());

	std::array < uint8_t,  4 > stxdata;
	auto stdit = stxdata.begin();
	std::copy(scmd.begin(), scmd.end(), stdit);
	stdit += 2;
	std::copy(scmd_pec.begin(), scmd_pec.end(), stdit);

	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = &this->gpio,
		.hspi = this->hspi,
		.pTxData = stxdata.begin(),
		.pRxData = nullptr,
		.dataSize = stxdata.size(),
	};

	SpiDmaManager::spiRequestAndWait(temp);

	return status;
}

template < class RdReg >
HAL_StatusTypeDef LTCController::rawRead(RCmd cmd, std::array < RdReg, chain_size > &data)
{
	HAL_StatusTypeDef status = HAL_OK;

	std::array < uint8_t, 2 > scmd = serializeCmd(cmd);
	std::array < uint8_t, 2 > scmd_pec = calcPEC(scmd.begin(), scmd.end());

	std::array < uint8_t, 4 > stxdata;
	auto stdit = stxdata.begin();
	std::copy(scmd.begin(), scmd.end(), stdit);
	stdit += 2;
	std::copy(scmd_pec.begin(), scmd_pec.end(), stdit);
	stdit += 2;

	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = &this->gpio,
		.hspi = this->hspi,
		.pTxData = stxdata.begin(),
		.pRxData = nullptr,
		.dataSize = stxdata.size(),
	};

	SpiDmaManager::spiRequestAndWait(temp);

	std::array < uint8_t, chain_size * 8 > rdata;

	temp.pTxData = nullptr;
	temp.pRxData = rdata.begin();
	temp.dataSize = rdata.size();

	SpiDmaManager::spiRequestAndWait(temp);

	for(auto rdit = rdata.begin(), dit = data.begin(); rdit != rdata.end() && dit != data.end();)
	{
		*dit = deserializeRegisterGroup<RdReg>(rdit);
		dit++;
		rdit += 8;
	}

	return status;
}

template< class RdReg >
HAL_StatusTypeDef LTCController::rawRead(RCmd cmd, std::array < RdReg, chain_size > &data, std::array < PecStatus, chain_size > &pec_status)
{
	HAL_StatusTypeDef status = HAL_OK;

	std::array < uint8_t, 2 > scmd = serializeCmd(cmd);
	std::array < uint8_t, 2 > scmd_pec = calcPEC(scmd.begin(), scmd.end());

	std::array < uint8_t, 4 > stxdata;
	auto stdit = stxdata.begin();
	std::copy(scmd.begin(), scmd.end(), stdit);
	stdit += 2;
	std::copy(scmd_pec.begin(), scmd_pec.end(), stdit);
	stdit += 2;

	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = &this->gpio,
		.hspi = this->hspi,
		.pTxData = stxdata.begin(),
		.pRxData = nullptr,
		.dataSize = stxdata.size(),
	};

	SpiDmaManager::spiRequestAndWait(temp);

	std::array < uint8_t, chain_size * 8 > rdata;

	temp.pTxData = nullptr;
	temp.pRxData = rdata.begin();
	temp.dataSize = rdata.size();

	SpiDmaManager::spiRequestAndWait(temp);
	auto rdit = rdata.begin();
	auto dit = data.begin();
	auto psit = pec_status.begin();
	for(; rdit != rdata.end() && dit != data.end();)
	{
		*dit = deserializeRegisterGroup<RdReg>(rdit);
		dit++;

		auto pec = calcPEC(rdit, rdit + 6);
		rdit += 6;

		if (pec[0] != rdit[0] || pec[1] != rdit[1]) *psit = PecStatus::Error;
		else *psit = PecStatus::Ok;

		rdit += 2;
		psit++;
	}


	return status;
}
