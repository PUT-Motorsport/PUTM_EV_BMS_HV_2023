/*
 * LTCController.cpp
 *
 *  Created on: 19 lip 2023
 *      Author: piotr
 */

#include <Controllers/Ltc6811Controller.hpp>
#include <Controllers/SpiDmaController.hpp>
#include <Utils/PEC15.hpp>
#include <algorithm>
#include <bitset>

extern GpioOut ams_status;

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
		configs[i].adcopt = 1;
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
LtcStatus Ltc6811Controller::rawRead(Ltc6811::RCmd cmd, RegArray < RdReg > *out, RegArray < LtcStatus > *out_pec)
{
	auto status = LtcStatus::Ok;

	static std::array < uint8_t, 4 + CHAIN_SIZE * 8 > stxdata { 0 };
	static std::array < uint8_t, 4 + CHAIN_SIZE * 8 > srxdata { 0 };

	auto stxdit = stxdata.begin();
	auto srxdit = srxdata.begin() + 4;
	auto odit	= out->begin();
	auto opit	= out_pec->begin();

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);

	SpiTxRxRequest request(cs, hspi, stxdata.begin(), srxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	for(size_t i = 0; i < LtcConfig::CHAIN_SIZE; i++)
	{
		auto srxditbeg 	= srxdit;
		auto srxditend 	= srxdit + 6;
		auto srxp0		= *(srxdit + 6);
		auto srxp1		= *(srxdit + 7);

		auto [ pec0, pec1 ] = calcPEC(srxditbeg, srxditend);
		if( pec0 != srxp0 || pec1 != srxp1)
		{
			*opit = LtcStatus::PecError;
			status = LtcStatus::PecError;
		}
		else
		{
			*opit = LtcStatus::Ok;
			deserializeRegisterGroup(odit, srxdit);
		}

		srxdit 	+= 8;
		odit	+= 1;
		opit	+= 1;
	}

	return status;
}

template < WriteReadRegisterGroup WrRdReg >
LtcStatus Ltc6811Controller::rawWrite(Ltc6811::WCmd cmd, RegArray < WrRdReg > const *data)
{
	auto status = LtcStatus::Ok;

	static std::array < uint8_t, 4 + CHAIN_SIZE * 8 > stxdata;
	auto stxdit = stxdata.begin();

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);
	stxdit += 4;

	for(auto rdit = data->rbegin(); rdit != data->rend(); rdit++)
	{
		serializeRegisterGroup(stxdit, *rdit);
		std::tie(stxdit[6], stxdit[7]) = calcPEC(stxdit, stxdit + 6);
		stxdit += 8;
	}

	SpiTxRequest request(cs, hspi, stxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	return status;
}
LtcStatus Ltc6811Controller::rawWrite(Ltc6811::WCmd cmd)
{
	auto status = LtcStatus::Ok;

	static std::array < uint8_t, 4 > stxdata;
	auto stxdit = stxdata.begin();

	std::tie(stxdit[0], stxdit[1]) = serializeCmd(cmd);
	std::tie(stxdit[2], stxdit[3]) = calcPEC(stxdit, stxdit + 2);

	SpiTxRequest request(cs, hspi, stxdata.begin(), stxdata.size());
	SpiDmaController::spiRequestAndWait(request);

	return status;
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

LtcStatus Ltc6811Controller::configure()
{
	wakeUp();
	return rawWrite(CMD_WRCFGA, &configs);
}

LtcStatus Ltc6811Controller::readPdVoltages(DataArray < float > *out)
{
	auto status = LtcStatus::Ok;

	static std::array < RegArray < CellVoltage >, 4> regs;
	static std::array < RegArray < LtcStatus >, 4 > pecs;

	for(size_t repeat = 0; repeat < 2; repeat++)
	{
		wakeUp();
		rawWrite(CMD_ADOW(Mode::Filtered, Pull::Down, Discharge::NotPermited, Cell::All));
		//rawWrite(CMD_ADCV(Mode::Normal, Discharge::NotPermited, Cell::All));
		osDelay(tadc);
	}

	wakeUp();
	rawRead(CMD_RDCVA, &regs[0], &pecs[0]);
	//wakeUp();
	rawRead(CMD_RDCVB, &regs[1], &pecs[1]);
	//wakeUp();
	rawRead(CMD_RDCVC, &regs[2], &pecs[2]);
	//wakeUp();
	rawRead(CMD_RDCVD, &regs[3], &pecs[3]);

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		for(size_t r = 0; r < 3; r++)
		{
			if(pecs[r][ltc] == LtcStatus::Ok)
			{
				out->at(ltc*12 + r*3 + 0) = convRawToU(regs[r][ltc].channel[0].val);
				out->at(ltc*12 + r*3 + 1) = convRawToU(regs[r][ltc].channel[1].val);
				out->at(ltc*12 + r*3 + 2) = convRawToU(regs[r][ltc].channel[2].val);
			}
			else
			{
				out->at(ltc*12 + r*3 + 0) = -1.0f;
				out->at(ltc*12 + r*3 + 1) = -1.0f;
				out->at(ltc*12 + r*3 + 2) = -1.0f;
			}
		}
	}

	return status;
}
LtcStatus Ltc6811Controller::readPuVoltages(DataArray < float > *out)
{
	auto status = LtcStatus::Ok;

	static std::array < RegArray < CellVoltage >, 4> regs;
	static std::array < RegArray < LtcStatus >, 4 > pecs;

	for(size_t repeat = 0; repeat < 2; repeat++)
	{
		wakeUp();
		rawWrite(CMD_ADOW(Mode::Filtered, Pull::Up, Discharge::NotPermited, Cell::All));
		//rawWrite(CMD_ADCV(Mode::Normal, Discharge::NotPermited, Cell::All));
		osDelay(tadc);
	}

	wakeUp();
	rawRead(CMD_RDCVA, &regs[0], &pecs[0]);
	//wakeUp();
	rawRead(CMD_RDCVB, &regs[1], &pecs[1]);
	//wakeUp();
	rawRead(CMD_RDCVC, &regs[2], &pecs[2]);
	//wakeUp();
	rawRead(CMD_RDCVD, &regs[3], &pecs[3]);

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		for(size_t r = 0; r < 4; r++)
		{
			if(pecs[r][ltc] == LtcStatus::Ok)
			{
				out->at(ltc*12 + r*3 + 0) = convRawToU(regs[r][ltc].channel[0].val);
				out->at(ltc*12 + r*3 + 1) = convRawToU(regs[r][ltc].channel[1].val);
				out->at(ltc*12 + r*3 + 2) = convRawToU(regs[r][ltc].channel[2].val);
			}
			else
			{
				out->at(ltc*12 + r*3 + 0) = -1.0f;
				out->at(ltc*12 + r*3 + 1) = -1.0f;
				out->at(ltc*12 + r*3 + 2) = -1.0f;
			}
		}
	}

	return status;
}

LtcStatus Ltc6811Controller::checkOpenWire(DataArray < bool > *out)
{
	auto status = LtcStatus::Ok;

	static DataArray < float > pd_v;
	static DataArray < float > pu_v;

	std::fill(out->begin(), out->end(), 0);

	readPdVoltages(&pd_v);
	readPuVoltages(&pu_v);

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		for(size_t cell = 0; cell < 12; cell++)
		{
			if(cell == 0)
			{
				if (pu_v[ltc * 12 + 0] < 2.f)
					out->at(ltc * 12 + 0) = true;
				continue;
			}
			if(cell == 11)
			{
				if (pd_v[ltc * 12 + 11] < 2.f)
				out->at(ltc * 12 + 11) = true;
				continue;
			}

			if (pu_v[ltc * 12 + cell] - pd_v[ltc * 12 + cell] < -0.4f)
				out->at(ltc * 12 + cell) = true;
		}
	}

	return status;
}

LtcStatus Ltc6811Controller::readVoltages(DataArray < float > *out)
{
	auto status = LtcStatus::Ok;

	static std::array < RegArray < CellVoltage >, 4> regs;
	static std::array < RegArray < LtcStatus >, 4 > pecs;

	ams_status.activate();
	wakeUp();
	rawWrite(CMD_ADOW(Mode::Normal, Pull::Down, Discharge::NotPermited, Cell::All));
	//rawWrite(CMD_ADCV(Mode::Filtered, Discharge::NotPermited, Cell::All));
	osDelay(tadc);

	wakeUp();
	rawRead(CMD_RDCVA, &regs[0], &pecs[0]);
	//wakeUp();
	rawRead(CMD_RDCVB, &regs[1], &pecs[1]);
	//wakeUp();
	rawRead(CMD_RDCVC, &regs[2], &pecs[2]);
	//wakeUp();
	rawRead(CMD_RDCVD, &regs[3], &pecs[3]);
	ams_status.deactivate();

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		for(size_t r = 0; r < 4; r++)
		{
			if(pecs[r][ltc] == LtcStatus::Ok)
			{
				out->at(ltc*12 + r*3 + 0) = convRawToU(regs[r][ltc].channel[0].val);
				out->at(ltc*12 + r*3 + 1) = convRawToU(regs[r][ltc].channel[1].val);
				out->at(ltc*12 + r*3 + 2) = convRawToU(regs[r][ltc].channel[2].val);
			}
			else
			{
				out->at(ltc*12 + r*3 + 0) = -1.0f;
				out->at(ltc*12 + r*3 + 1) = -1.0f;
				out->at(ltc*12 + r*3 + 2) = -1.0f;
			}
		}
	}

	return status;
}

LtcStatus Ltc6811Controller::setDischarge(DataArray < bool > const *in)
{
	auto status = LtcStatus::Ok;

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		configs[ltc].dcc1  = in->at(ltc * 12 + 0);
		configs[ltc].dcc2  = in->at(ltc * 12 + 1);
		configs[ltc].dcc3  = in->at(ltc * 12 + 2);
		configs[ltc].dcc4  = in->at(ltc * 12 + 3);
		configs[ltc].dcc5  = in->at(ltc * 12 + 4);
		configs[ltc].dcc6  = in->at(ltc * 12 + 5);
		configs[ltc].dcc7  = in->at(ltc * 12 + 6);
		configs[ltc].dcc8  = in->at(ltc * 12 + 7);
		configs[ltc].dcc9  = in->at(ltc * 12 + 8);
		configs[ltc].dcc10 = in->at(ltc * 12 + 9);
		configs[ltc].dcc11 = in->at(ltc * 12 + 10);
		configs[ltc].dcc12 = in->at(ltc * 12 + 11);
	}

	wakeUp();
	rawWrite(CMD_WRCFGA, &configs);

	return status;
}

LtcStatus Ltc6811Controller::readGpio(GpioArray < float > *out)
{
	auto status = LtcStatus::Ok;

	static RegArray < AuxilliaryVoltageA > reg_a;
	static RegArray < AuxilliaryVoltageB > reg_b;
	static RegArray < LtcStatus > pec_a;
	static RegArray < LtcStatus > pec_b;

	wakeUp();
	rawWrite(CMD_ADAX(Mode::Normal, Pin::All));
	osDelay(tadc);

	wakeUp();
	rawRead(CMD_RDAUXA, &reg_a, &pec_a);
	rawRead(CMD_RDAUXB, &reg_b, &pec_b);

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		size_t offset = ltc * 5;
		if(pec_a[ltc] == LtcStatus::Ok)
		{
			out->at(0 + offset) = float(reg_a[ltc].gpio[0].val / 10'000.f);
			out->at(1 + offset) = float(reg_a[ltc].gpio[1].val / 10'000.f);
			out->at(2 + offset) = float(reg_a[ltc].gpio[2].val / 10'000.f);
		}
		else
		{
			out->at(0 + offset) = -1.f;
			out->at(1 + offset) = -1.f;
			out->at(2 + offset) = -1.f;
		}
		if(pec_b[ltc] == LtcStatus::Ok)
		{
			out->at(3 + offset) = float(reg_b[ltc].gpio[0].val / 10'000.f);
			out->at(4 + offset) = float(reg_b[ltc].gpio[1].val / 10'000.f);
		}
		else
		{
			out->at(3 + offset) = -1.f;
			out->at(4 + offset) = -1.f;
		}
	}

	return status;
}

LtcStatus Ltc6811Controller::readStackVoltage(float *out)
{
	auto status = LtcStatus::Ok;

	static RegArray < StatusA > reg;
	static RegArray < LtcStatus > pec;

	wakeUp();
	rawWrite(CMD_ADCVSC(Mode::Normal, Discharge::Permitted));

	osDelay(tadc);

	wakeUp();
	rawRead<StatusA>(CMD_RDSTATA, &reg, &pec);

	float accumulator = 0.f;

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		if(pec[ltc] == LtcStatus::Ok)
		{
			accumulator += convRawToSU(reg[ltc].sc);
		}
		else
		{
			status = LtcStatus::PecError;
			break;
		}
	}

	if(status == LtcStatus::Ok)
	{
		*out = accumulator;
	}
	else
	{
		*out = -1.f;
	}

	return status;
}
