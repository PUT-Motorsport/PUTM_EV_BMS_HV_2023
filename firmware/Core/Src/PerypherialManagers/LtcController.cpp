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
#include <tuple>

using namespace LTC6811;

LtcController::LtcController(GpioOut cs, SPI_HandleTypeDef &hspi) : hspi(hspi), cs(cs)
{
	cs.deactivate();

	for(auto cfg : configs)
	{
		// set gpio pull down to OFF
		cfg.gpio1 = 1;
		cfg.gpio2 = 1;
		cfg.gpio3 = 1;
		cfg.gpio4 = 1;
		cfg.gpio5 = 1;
		// set reference to shut down after conversion
		cfg.refon = 0;
		// set adc clock to use higher speeds
		cfg.adcopt = 0;
		// set all discharges to off
		cfg.dcc1 	= 0;
		cfg.dcc2 	= 0;
		cfg.dcc3 	= 0;
		cfg.dcc4 	= 0;
		cfg.dcc5 	= 0;
		cfg.dcc6 	= 0;
		cfg.dcc7 	= 0;
		cfg.dcc8 	= 0;
		cfg.dcc9 	= 0;
		cfg.dcc10 	= 0;
		cfg.dcc11 	= 0;
		cfg.dcc12 	= 0;
		//set under voltage comparison voltage
		cfg.vuv_lsb = uint8_t(vuv & 0xff);
		cfg.vuv_msb = uint8_t((vuv >> 8) & 0x0f);
		//set over voltage comparison voltage
		cfg.vov_lsb = uint8_t(vuv & 0x0f);
		cfg.vov_msb = uint8_t((vuv >> 4) & 0xff);
		//set discharge time
		cfg.dcto = uint8_t(DischargeTime::Disable);
	}
}

template < WriteReadRegisterGroup WrRdReg >
LtcCtrlStatus LtcController::rawWrite(WCmd cmd, std::array< WrRdReg, chain_size > const &data)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	std::array < uint8_t, 4 + chain_size * 8 > stxdata;
	auto stxdit = stxdata.begin();

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);
	stxdit += 4;

	for(auto& d : data)
	{
		serializeRegisterGroup(stxdit, d);
		std::tie(stxdit[6], stxdit[7]) = calcPEC(stxdit, stxdit + 6);
		stxdit += 8;
	}

	SpiTxRequest request(cs, hspi, stxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	return status;
}

LtcCtrlStatus LtcController::rawWrite(WCmd cmd)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	std::array < uint8_t, 4 > stxdata;
	auto stxdit = stxdata.begin();

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);
	stxdit += 4;

	SpiTxRequest request(cs, hspi, stxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	return status;
}

template < ReadRegisterGroup RdReg >
LtcCtrlStatus LtcController::rawRead(RCmd cmd, std::array < RdReg, chain_size > &data)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	std::array < uint8_t, 4 + chain_size * 8 > stxdata;
	std::array < uint8_t, 4 + chain_size * 8 > srxdata;
	auto stxdit = stxdata.begin();
	auto srxdit = srxdata.begin() + 4;

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);

	SpiTxRxRequest request(cs, hspi, stxdata.begin(), srxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	for(auto& d : data)
	{
		d = deserializeRegisterGroup< RdReg >(srxdit);
		srxdit += 8;
	}

	return status;
}

template< ReadRegisterGroup RdReg >
LtcCtrlStatus LtcController::rawRead(RCmd cmd, std::array < RdReg, chain_size > &data, std::array < PecStatus, chain_size > &pec_status)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	std::array < uint8_t, 4 + chain_size * 8 > stxdata;
	std::array < uint8_t, 4 + chain_size * 8 > srxdata;
	auto stxdit = stxdata.begin();
	auto srxdit = srxdata.begin() + 4;
	auto pecit = pec_status.begin();

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);

	SpiTxRxRequest request(cs, hspi, stxdata.begin(), srxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	for(auto& d : data)
	{
		deserializeRegisterGroup(d, srxdit);
		auto [ pec1, pec0 ] = calcPEC(srxdit, srxdit + 6);
		if( pec1 != srxdit[6] || pec0 != srxdit[7]) *pecit = PecStatus::Error;
		else *pecit = PecStatus::Ok;
		srxdit += 8;
		pecit++;
	}

	return status;
}

void LtcController::wakeUp()
{
	cs.activate();
	osDelay(twake_full);
	cs.deactivate();
	osDelay(twake_full);
}

void LtcController::handleWatchDog()
{
	auto cmd = CMD_RDCFGA;

	std::array < uint8_t, 4 > stxdata;
	auto stxdit = stxdata.begin();

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);
	stxdit += 4;

	SpiTxRequest request(cs, hspi, stxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);
}

PollStatus LtcController::pollAdcStatus()
{
	std::array < uint8_t, 4 + chain_size > tx;
	std::array < uint8_t, 4 + chain_size > rx;

	std::tie(tx[0], tx[1]) = serializeCmd(CMD_PLADC);
	std::tie(tx[2], tx[3]) = calcPEC(tx.begin(), tx.begin() + 2);

	SpiTxRxRequest request(cs, hspi, tx.begin(), rx.begin(), tx.size());
	SpiDmaController::spiRequestAndWait(request);

	//fill first 4 vals since they are trash anyway
	std::fill(rx.begin(), rx.begin() + 4, 1);
	for(auto s : rx)
		if(s == 0) return PollStatus::Busy;
	return PollStatus::Done;
}

LtcCtrlStatus LtcController::configure()
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	//std::array < Config, chain_size > configs_buff;
	//std::array < PecStatus, chain_size > pecs;

	wakeUp();
	rawWrite(CMD_WRCFGA, configs);
	//TODO: check config? for now i threw it out

	return status;
}

LtcCtrlStatus LtcController::readVoltages(std::array< std::array< float, 12 >, chain_size > &vol)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;
	std::array < std::array < PecStatus, chain_size >, 4 > pecs;
	std::array < std::array < CellVoltage, chain_size >, 4 > raw;

	//wakeUp();
	rawWrite(CMD_ADCV(Mode::Normal, Discharge::Permitted, Cell::All));

	osDelay(10);

	//wakeUp();
	rawRead(CMD_RDCVA, raw[0], pecs[0]);
	rawRead(CMD_RDCVB, raw[1], pecs[1]);
	rawRead(CMD_RDCVC, raw[2], pecs[2]);
	rawRead(CMD_RDCVD, raw[3], pecs[3]);

	for(size_t ltc = 0; ltc < chain_size; ltc++)
	{
		for(size_t cell = 0; cell < 12; cell++)
		{
			size_t reg = cell / 4;
			size_t rcell = cell % 3;
			if(pecs[reg][ltc] == PecStatus::Ok)
				vol[ltc][cell] = convRawToU(raw[reg][ltc].cell[rcell].val);
			else
				vol[ltc][cell] = -1.f;
		}
	}

	return status;
}

LtcCtrlStatus LtcController::diagnose(std::array < LtcDiagnosisStatus, chain_size > &diag)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	return status;
}

LtcCtrlStatus LtcController::balance(std::array < std::array < bool, 12 >, chain_size > &bal)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	return status;
}

LtcCtrlStatus LtcController::readGpioAndRef2(std::array< std::array< float, 6 >, chain_size > &aux)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;
	//std::array < std::array < PecStatus, chain_size >, 2 > pecs;
	//std::array < std::array < CellVoltage, chain_size >, 2 > raw;
	std::array < PecStatus, chain_size > pec_a;
	std::array < PecStatus, chain_size > pec_b;
	std::array < AuxilliaryVoltageA, chain_size > aux_a;
	std::array < AuxilliaryVoltageB, chain_size > aux_b;

	//wakeUp();
	rawWrite(CMD_ADAX(Mode::Normal, Pin::All));

	osDelay(10);

	//wakeUp();
	rawRead(CMD_RDAUXA, aux_a, pec_a);
	rawRead(CMD_RDAUXB,	aux_b, pec_b);

	for(size_t ltc = 0; ltc < chain_size; ltc++)
	{
		for(size_t gpio = 0; gpio < 3; gpio++)
		{
			if(pec_a[ltc] != PecStatus::Ok)
				aux[ltc][gpio] = -1.f;
			else
				aux[ltc][gpio] = convRawToGT(aux_a[ltc].gpio[gpio].val);
		}
		for(size_t gpio = 0; gpio < 2; gpio++)
		{
			if(pec_b[ltc] != PecStatus::Ok)
				aux[ltc][gpio] = -1.f;
			else
				aux[ltc][gpio] = convRawToGT(aux_b[ltc].gpio[gpio].val);
		}
		if(pec_b[ltc] != PecStatus::Ok)
			aux[ltc][5] = -1.f;
		else
			aux[ltc][5] = convRawToU(aux_b[ltc].ref.val);
	}

	return status;
}
