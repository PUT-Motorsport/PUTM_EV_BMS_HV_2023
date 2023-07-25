/*
 * LTCController.cpp
 *
 *  Created on: 19 lip 2023
 *      Author: piotr
 */

#include <PerypherialManagers/LtcController.hpp>
#include <PerypherialManagers/SpiDmaController.hpp>
#include "PerypherialManagers/LTC6811CmdCodes.hpp"
#include "task.h"

LtcController::LtcController(GpioOut gpio, SPI_HandleTypeDef* hspi) : hspi(hspi), gpio(gpio)
{
	gpio.deactivate();

	for(auto conf : configs)
	{
		// set gpio pull down to OFF
		conf.gpio1 = 1;
		conf.gpio2 = 1;
		conf.gpio3 = 1;
		conf.gpio4 = 1;
		conf.gpio5 = 1;
		// set reference to shut down after conversion
		conf.refon = 0;
		// set adc clock to use higher speeds
		conf.adcopt = 0;
		// set all discharges to off
		conf.dcc1 	= 0;
		conf.dcc2 	= 0;
		conf.dcc3 	= 0;
		conf.dcc4 	= 0;
		conf.dcc5 	= 0;
		conf.dcc6 	= 0;
		conf.dcc7 	= 0;
		conf.dcc8 	= 0;
		conf.dcc9 	= 0;
		conf.dcc10 	= 0;
		conf.dcc11 	= 0;
		conf.dcc12 	= 0;
		//set under voltage comparison voltage
		conf.vuv_lsb = uint8_t(vuv & 0xff);
		conf.vuv_msb = uint8_t((vuv >> 8) & 0x0f);
		//set over voltage comparison voltage
		conf.vov_lsb = uint8_t(vuv & 0x0f);
		conf.vov_msb = uint8_t((vuv >> 4) & 0xff);
		//set discharge time
		conf.dcto = uint8_t(LTC6811::DischargeTime::Disable);
	}
}

template < class WrRdReg >
LtcCtrlStatus LtcController::rawWrite(WCmd cmd, std::array< WrRdReg, chain_size > const &data)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

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
		auto sd_pec = calcPEC(sd.begin(), sd.end());
		std::copy(sd.begin(), sd.end(), stdit);
		std::copy(sd_pec.begin(), sd_pec.end(), stdit);
		stdit += 8;
	}

	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = nullptr,//&this->gpio,
		.hspi = this->hspi,
		.pTxData = stxdata.begin(),
		.pRxData = nullptr,
		.dataSize = stxdata.size(),
	};

	SpiDmaController::spiRequestAndWait(temp);

	return status;
}

LtcCtrlStatus LtcController::rawWrite(WCmd cmd)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

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
		.cs = nullptr,//&this->gpio,
		.hspi = this->hspi,
		.pTxData = stxdata.begin(),
		.pRxData = nullptr,
		.dataSize = stxdata.size(),
	};

	SpiDmaController::spiRequestAndWait(temp);

	return status;
}

template < class RdReg >
LtcCtrlStatus LtcController::rawRead(RCmd cmd, std::array < RdReg, chain_size > &data)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

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
		.cs = nullptr,//&this->gpio,
		.hspi = this->hspi,
		.pTxData = stxdata.begin(),
		.pRxData = nullptr,
		.dataSize = stxdata.size(),
	};

	SpiDmaController::spiRequestAndWait(temp);

	std::array < uint8_t, chain_size * 8 > rdata;

	temp.pTxData = nullptr;
	temp.pRxData = rdata.begin();
	temp.dataSize = rdata.size();

	SpiDmaController::spiRequestAndWait(temp);

	for(auto rdit = rdata.begin(), dit = data.begin(); rdit != rdata.end() && dit != data.end();)
	{
		*dit = deserializeRegisterGroup<RdReg>(rdit);
		dit++;
		rdit += 8;
	}

	return status;
}

template< class RdReg >
LtcCtrlStatus LtcController::rawRead(RCmd cmd, std::array < RdReg, chain_size > &data, std::array < PecStatus, chain_size > &pec_status)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

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
		.cs = nullptr,//&this->gpio,
		.hspi = this->hspi,
		.pTxData = stxdata.begin(),
		.pRxData = nullptr,
		.dataSize = stxdata.size(),
	};

	SpiDmaController::spiRequestAndWait(temp);

	std::array < uint8_t, chain_size * 8 > rdata;

	temp.pTxData = nullptr;
	temp.pRxData = rdata.begin();
	temp.dataSize = rdata.size();

	SpiDmaController::spiRequestAndWait(temp);
	auto rdit = rdata.begin();
	auto dit = data.begin();
	auto psit = pec_status.begin();
	for(; rdit != rdata.end() || dit != data.end();)
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

void LtcController::wakeUp()
{
	uint8_t dummy_cmd = 0;
	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = nullptr, //&this->gpio,
		.hspi = this->hspi,
		.pTxData = &dummy_cmd,
		.pRxData = nullptr,
		.dataSize = 1,
	};

	gpio.activate();
	SpiDmaController::spiRequestAndWait(temp);
	osDelay(Config::twake_full);
	SpiDmaController::spiRequestAndWait(temp);
	osDelay(Config::twake_full);
	gpio.deactivate();
}

void LtcController::handleWatchDog()
{
	//TODO: also some dummy rdcnfg?

	uint8_t dummy_cmd = 0;
	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = nullptr,//&this->gpio,
		.hspi = this->hspi,
		.pTxData = &dummy_cmd,
		.pRxData = nullptr,
		.dataSize = 1,
	};

	gpio.activate();
	SpiDmaController::spiRequestAndWait(temp);
	osDelay(Config::twake_full);
	gpio.deactivate();
}

PollStatus LtcController::pollAdcStatus()
{
	rawWrite(CMD_PLADC);

	uint8_t result;
	SpiDmaHandle temp =
	{
		.taskToNotify = xTaskGetCurrentTaskHandle(),
		.cs = nullptr, //&this->gpio,
		.hspi = this->hspi,
		.pTxData = nullptr,
		.pRxData = &result,
		.dataSize = 1,
	};

	gpio.activate();
	SpiDmaController::spiRequestAndWait(temp);
	gpio.deactivate();

	if(result == 0) return PollStatus::Busy;
	return PollStatus::Done;
}

LtcCtrlStatus LtcController::configure()
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;
	bool status_lock = false;

	std::array < LTC6811::Config, chain_size > configs_buff;
	std::array < PecStatus, chain_size > pecs;

	gpio.activate();
	rawWrite(CMD_WRCFGA, configs);
	osDelay(10);
	rawRead(CMD_RDCFGA, configs_buff, pecs);
	gpio.deactivate();

	for(size_t i = 0; i < chain_size; i++)
	{
		if(not LTC6811::RegEq(configs[i], configs_buff[i]))
		{
			if(!status_lock)
			{
				status = LtcCtrlStatus::RegValMismatchError;
				status_lock = true;
			}
		}
		if(pecs[i] == PecStatus::Error)
		{
			if(!status_lock)
			{
				status = LtcCtrlStatus::PecError;
				status_lock = true;
			}
		}
	}

	return status;
}

LtcCtrlStatus LtcController::readVoltages(std::array< std::array< float, 12 >, chain_size > &vol)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;
	std::array < PecStatus, chain_size > pecs;
	std::array < std::array < LTC6811::CellVoltage, chain_size >, 4 > cell_v_buff;

	gpio.activate();
	rawWrite(CMD_ADCV(Mode::Normal, Discharge::Permitted, Cell::All));

	//while(pollAdcStatus() == PollStatus::Busy)
	osDelay(10);

	rawRead(CMD_RDCVA, cell_v_buff[0], pecs);
	rawRead(CMD_RDCVB, cell_v_buff[1], pecs);
	rawRead(CMD_RDCVC, cell_v_buff[2], pecs);
	rawRead(CMD_RDCVD, cell_v_buff[3], pecs);
	gpio.deactivate();

	for(size_t stage = 0; stage < 4; stage++)
	{
		for(size_t i = 0; i < chain_size; i++)
		{
			//TODO: cos innego ogarnąć jak pec error?
			//bo imo zwracanie -1 jest takie mało optymalne?
			//FIXME: coś średnio działa
			if(pecs[i] == PecStatus::Error)
			{
				status = LtcCtrlStatus::PecError;
				for(size_t j = 0; j < 3; j ++)
					vol[i][j + stage] = -1.f;
			}
			else
			{
				for(size_t j = 0; j < 3; j ++)
					vol[i][j + stage] = LTC6811::CellVConv(cell_v_buff[stage][i].cell[j].val);
			}
		}
	}

	return status;
}
