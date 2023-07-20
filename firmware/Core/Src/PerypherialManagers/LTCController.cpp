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

template < size_t chain_size >
LTCController< chain_size >::LTCController(GpioOut gpio, SPI_HandleTypeDef* hspi) : hspi(hspi), gpio(gpio)
{
	usingLock(gpio, [&]()
	{
		gpio.deactivate();
	});
}

template < size_t chain_size >
void LTCController< chain_size >::wakeUp()
{
	uint8_t dummy_cmd = 0;
	SpiDmaHandle temp =
	{
		.cs = &this->gpio,
		.dataSize = 1,
		.hspi = this->hspi,
		.pRxData = nullptr,
		.pTxData = &dummy_cmd,
		.taskToNotify = xTaskGetCurrentTaskHandle()
	};

	SpiDmaManager::spiRequestAndWait(temp);
	osDelay(Config::twake_full);
	SpiDmaManager::spiRequestAndWait(temp);
	osDelay(Config::twake_full);
	//HAL_SPI_Transmit(hspi, &dummy_cmd, 1, 100);
	//HAL_Delay(Config::twake_full);
	//HAL_SPI_Transmit(hspi, &dummy_cmd, 1, 100);
	//HAL_Delay(Config::twake_full);
}

template < size_t chain_size >
void LTCController< chain_size >::handleWatchDog()
{
	//TODO: also some dummy rdcnfg?

	uint8_t dummy_cmd = 0;
	SpiDmaHandle temp =
	{
		.cs = &this->gpio,
		.dataSize = 1,
		.hspi = this->hspi,
		.pRxData = nullptr,
		.pTxData = &dummy_cmd,
		.taskToNotify = xTaskGetCurrentTaskHandle()
	};

	SpiDmaManager::spiRequestAndWait(temp);
	osDelay(Config::twake_full);
}

template < size_t chain_size >
template < class WrRdReg >
HAL_StatusTypeDef LTCController< chain_size >::rawWrite(WCmd cmd, std::array< WrRdReg, chain_size > const &data)
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
		.cs = &this->gpio,
		.dataSize = stxdata.size(),
		.hspi = this->hspi,
		.pRxData = nullptr,
		.pTxData = stxdata.begin(),
		.taskToNotify = xTaskGetCurrentTaskHandle()
	};

	SpiDmaManager::spiRequestAndWait(temp);

	return status;
}

template < size_t chain_size >
HAL_StatusTypeDef LTCController< chain_size >::rawWrite(WCmd cmd)
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
		.cs = &this->gpio,
		.dataSize = stxdata.size(),
		.hspi = this->hspi,
		.pRxData = nullptr,
		.pTxData = stxdata.begin(),
		.taskToNotify = xTaskGetCurrentTaskHandle()
	};

	SpiDmaManager::spiRequestAndWait(temp);

	return status;
}


template < size_t chain_size >
template < class RdReg >
HAL_StatusTypeDef LTCController< chain_size >::rawRead(RCmd cmd, std::array < RdReg, chain_size > &data)
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
		.cs = &this->gpio,
		.dataSize = stxdata.size(),
		.hspi = this->hspi,
		.pRxData = nullptr,
		.pTxData = stxdata.begin(),
		.taskToNotify = xTaskGetCurrentTaskHandle()
	};

	SpiDmaManager::spiRequestAndWait(temp);

	std::array < uint8_t, chain_size * 8 > rdata;

	temp.pTxData = nullptr;
	temp.pRxData = rdata.begin();
	temp.dataSize = rdata.size();

	SpiDmaManager::spiRequestAndWait(temp);

	for(auto rdit = rdata.begin(), dit = data.begin(); rdit != rdata.end() && dit != data.end();)
	{
		*dit = deserializeRegisterGroup(rdit);
		dit++;
		rdit += 8;
	}

	return status;
}

template < size_t chain_size >
template< class RdReg >
HAL_StatusTypeDef LTCController< chain_size >::rawRead(RCmd cmd, std::array < RdReg, chain_size > &data, std::array < PecStatus, chain_size > &pec_status)
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
		.cs = &this->gpio,
		.dataSize = stxdata.size(),
		.hspi = this->hspi,
		.pRxData = nullptr,
		.pTxData = stxdata.begin(),
		.taskToNotify = xTaskGetCurrentTaskHandle()
	};

	SpiDmaManager::spiRequestAndWait(temp);

	std::array < uint8_t, chain_size * 8 > rdata;

	temp.pTxData = nullptr;
	temp.pRxData = rdata.begin();
	temp.dataSize = rdata.size();

	SpiDmaManager::spiRequestAndWait(temp);

	for(auto rdit = rdata.begin(), dit = data.begin(), psit = pec_status.begin(); rdit != rdata.end() && dit != data.end();)
	{
		*dit = deserializeRegisterGroup(rdit);
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
