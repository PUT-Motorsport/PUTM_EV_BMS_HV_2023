/*
 * LTCController.cpp
 *
 *  Created on: 19 lip 2023
 *      Author: piotr
 */

#include <PerypherialManagers/Ltc6811Controller.hpp>
#include <Utils/PEC15.hpp>
#include <PerypherialManagers/SpiDmaController.hpp>
#include <algorithm>
#include <bitset>

using namespace Ltc6811;
using namespace LtcConfig;

Ltc6811Controller::Ltc6811Controller(GpioOut cs, SPI_HandleTypeDef &hspi) : hspi(hspi), cs(cs)
{
	//cs.deactivate();

	//for(auto cfg : configs)
	for(size_t i = 0; i < CHAIN_SIZE; i++)
	{
		// set gpio pull down to OFF
		configs[i].gpio1 = 1;
		configs[i].gpio2 = 1;
		configs[i].gpio3 = 1;
		configs[i].gpio4 = 1;
		configs[i].gpio5 = 1;
		// set reference to shut down after conversion
		configs[i].refon = 0;
		// set adc clock to use higher speeds
		configs[i].adcopt = 0;
		// set all discharges to off
		configs[i].dcc1 = 0;
		configs[i].dcc2 = 0;
		configs[i].dcc3 = 0;
		configs[i].dcc4 = 0;
		configs[i].dcc5 = 0;
		configs[i].dcc6 = 0;
		configs[i].dcc7 = 0;
		configs[i].dcc8 = 0;
		configs[i].dcc9 = 0;
		configs[i].dcc10 = 0;
		configs[i].dcc11 = 0;
		configs[i].dcc12 = 0;
		//set under voltage comparison voltage
		configs[i].vuv = vuv;
		//set over voltage comparison voltage
		configs[i].vov = vov;
		//set soft watch dog timer discharge time (can't be used in our case)
		configs[i].dcto = DischargeTime::Disable;
	}
}

template < Ltc6811::ReadRegisterGroup RdReg >
std::array < std::variant < RdReg, LtcError >, CHAIN_SIZE > Ltc6811Controller::rawRead(Ltc6811::RCmd cmd)
{
	static std::array < uint8_t, 4 + CHAIN_SIZE * 8 > stxdata { 0 };
	static std::array < uint8_t, 4 + CHAIN_SIZE * 8 > srxdata { 0 };
	static std::array < std::variant < RdReg, LtcError >, CHAIN_SIZE > data;

	auto stxdit = stxdata.begin();
	auto srxdit = srxdata.begin() + 4;

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);

	SpiTxRxRequest request(cs, hspi, stxdata.begin(), srxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	for(auto& dit : data)
	{
		auto srxditbeg 	= srxdit;
		auto srxditend 	= srxdit + 6;
		auto srxp0		= *(srxdit + 6);
		auto srxp1		= *(srxdit + 7);

		auto [ pec0, pec1 ] = calcPEC(srxditbeg, srxditend);
		if( pec0 != srxp0 || pec1 != srxp1)
			dit = LtcError::PecError;
		else
			dit = deserializeRegisterGroup<RdReg>(srxdit);
		srxdit += 8;
	}

	return data;
}

template < WriteReadRegisterGroup WrRdReg >
std::optional < LtcError > Ltc6811Controller::rawWrite(WCmd cmd, std::array < WrRdReg, CHAIN_SIZE > const &data)
{
	static std::array < uint8_t, 4 + CHAIN_SIZE * 8 > stxdata;
	auto stxdit = stxdata.begin();

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);
	stxdit += 4;

	for(auto rdit = data.rbegin(); rdit != data.rend(); rdit++)
	{
		serializeRegisterGroup(stxdit, *rdit);
		std::tie(stxdit[6], stxdit[7]) = calcPEC(stxdit, stxdit + 6);
		stxdit += 8;
	}

	SpiTxRequest request(cs, hspi, stxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	return { };
}

std::optional < LtcError > Ltc6811Controller::rawWrite(WCmd cmd)
{
	static std::array < uint8_t, 4 > stxdata;
	auto stxdit = stxdata.begin();

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);

	SpiTxRequest request(cs, hspi, stxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	return { };
}

void Ltc6811Controller::wakeUp()
{
	uint8_t dummy = 0;
	SpiTxRequest request(cs, hspi, &dummy, 1);
	SpiDmaController::spiRequestAndWait(request);
	osDelay(twake_full);
}

void Ltc6811Controller::handleWatchDog()
{
	rawWrite(CMD_PLADC);
}

PollStatus Ltc6811Controller::pollAdcStatus()
{
	std::array < uint8_t, 4 + CHAIN_SIZE > tx;
	std::array < uint8_t, 4 + CHAIN_SIZE > rx;

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

std::optional < LtcError > Ltc6811Controller::configure()
{
	wakeUp();
	return rawWrite(CMD_WRCFGA, configs);
}

std::array < std::variant < LtcError, float > , LtcConfig::CHAIN_SIZE * 5 > Ltc6811Controller::readGpio()
{
	static std::array < std::variant < LtcError, float >, LtcConfig::CHAIN_SIZE * 5 > array;

	wakeUp();
	rawWrite(CMD_ADAX(Mode::Normal, Pin::All));

	osDelay(tadc);

	wakeUp();
	auto reg_a = rawRead<AuxilliaryVoltageA>(CMD_RDAUXA);
	wakeUp();
	auto reg_b = rawRead<AuxilliaryVoltageB>(CMD_RDAUXB);

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		size_t offset = ltc * 5;
		if(std::holds_alternative<AuxilliaryVoltageA>(reg_a[ltc]))
		{
			array[0 + offset] = float(std::get<AuxilliaryVoltageA>(reg_a[ltc]).gpio[0].val);
			array[1 + offset] = float(std::get<AuxilliaryVoltageA>(reg_a[ltc]).gpio[1].val);
			array[2 + offset] = float(std::get<AuxilliaryVoltageA>(reg_a[ltc]).gpio[2].val);
		}
		else
		{
			array[0 + offset] = LtcError::Error;
			array[1 + offset] = LtcError::Error;
			array[2 + offset] = LtcError::Error;
		}
		if(std::holds_alternative<AuxilliaryVoltageB>(reg_b[ltc]))
		{
			array[3 + offset] = float(std::get<AuxilliaryVoltageB>(reg_b[ltc]).gpio[0].val);
			array[4 + offset] = float(std::get<AuxilliaryVoltageB>(reg_b[ltc]).gpio[1].val);
		}
		else
		{
			array[3 + offset] = LtcError::Error;
			array[4 + offset] = LtcError::Error;
		}
	}

	return array;
}

std::array < std::variant < LtcError, float > , CHAIN_SIZE * 12 > Ltc6811Controller::readVoltages()
{
	static std::array < std::variant < LtcError, float > , CHAIN_SIZE * 12 > array;
	static std::array < std::array < std::variant < CellVoltage, LtcError >, CHAIN_SIZE >, 4 > regs;

	wakeUp();
	rawWrite(CMD_ADCV(Mode::Normal, Discharge::NotPermited, Cell::All));

	osDelay(tadc);

	wakeUp();
	regs[0] = rawRead<CellVoltage>(CMD_RDCVA);
	wakeUp();
	regs[1] = rawRead<CellVoltage>(CMD_RDCVB);
	wakeUp();
	regs[2] = rawRead<CellVoltage>(CMD_RDCVC);
	wakeUp();
	regs[3] = rawRead<CellVoltage>(CMD_RDCVD);

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		for(size_t r = 0; r < 4; r++)
		{
			if(std::holds_alternative<CellVoltage>(regs[r][ltc]))
			{
				array[ltc*12 + r*3 + 0] = convRawToU(std::get<CellVoltage>(regs[r][ltc]).channel[0].val);
				array[ltc*12 + r*3 + 1] = convRawToU(std::get<CellVoltage>(regs[r][ltc]).channel[1].val);
				array[ltc*12 + r*3 + 2] = convRawToU(std::get<CellVoltage>(regs[r][ltc]).channel[2].val);
			}
			else
			{
				array[ltc*12 + r*3 + 0] = LtcError::Error;
				array[ltc*12 + r*3 + 1] = LtcError::Error;
				array[ltc*12 + r*3 + 2] = LtcError::Error;
			}
		}
	}

	return array;
}

std::optional < LtcError > Ltc6811Controller::setDischarge(const std::array< bool, CHAIN_SIZE * 12 > &dis)
{
	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc)
	{
		configs[ltc].dcc1  = dis[ltc * 12 + 0];
		configs[ltc].dcc2  = dis[ltc * 12 + 1];
		configs[ltc].dcc3  = dis[ltc * 12 + 2];
		configs[ltc].dcc4  = dis[ltc * 12 + 3];
		configs[ltc].dcc5  = dis[ltc * 12 + 4];
		configs[ltc].dcc6  = dis[ltc * 12 + 5];
		configs[ltc].dcc7  = dis[ltc * 12 + 6];
		configs[ltc].dcc8  = dis[ltc * 12 + 7];
		configs[ltc].dcc9  = dis[ltc * 12 + 8];
		configs[ltc].dcc10 = dis[ltc * 12 + 9];
		configs[ltc].dcc11 = dis[ltc * 12 + 10];
		configs[ltc].dcc12 = dis[ltc * 12 + 11];
	}

	wakeUp();
	rawWrite(CMD_WRCFGA, configs);

	return { };
}

std::variant < LtcError, float > Ltc6811Controller::readStackVoltage()
{
	wakeUp();
	rawWrite(CMD_ADCVSC(Mode::Normal, Discharge::Permitted));

	osDelay(tadc);

	wakeUp();
	auto reg = rawRead<StatusA>(CMD_RDSTATA);

	float accumulator = 0.f;

	for(size_t i = 0; i < CHAIN_SIZE; i++)
	{
		if(std::holds_alternative<StatusA>(reg[i]))
		{
			accumulator += convRawToSU(std::get<StatusA>(reg[i]).sc);
		}
		else
		{
			return { LtcError::PecError };
		}
	}

	return { accumulator };
}
