/*
 * LTCController.cpp
 *
 *  Created on: 19 lip 2023
 *      Author: piotr
 */

#include <Utils/PEC15.hpp>
#include <PerypherialManagers/LTC6811Controller.hpp>
#include <PerypherialManagers/SpiDmaController.hpp>

using namespace LTC6811;
using namespace Ltc;

LTC6811Controller::LTC6811Controller(GpioOut cs, SPI_HandleTypeDef &hspi) : hspi(hspi), cs(cs)
{
	cs.deactivate();

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
		configs[i].vuv_lsb = uint8_t(vuv & 0xff);
		configs[i].vuv_msb = uint8_t((vuv >> 8) & 0x0f);
		//set over voltage comparison voltage
		configs[i].vov_lsb = uint8_t(vuv & 0x0f);
		configs[i].vov_msb = uint8_t((vuv >> 4) & 0xff);
		//set soft watch dog timer discharge time (can't be used in our case)
		configs[i].dcto = uint8_t(DischargeTime::Disable);
	}
}

template < WriteReadRegisterGroup WrRdReg >
LtcCtrlStatus LTC6811Controller::rawWrite(WCmd cmd, std::array< WrRdReg, CHAIN_SIZE > const &data)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	std::array < uint8_t, 4 + CHAIN_SIZE * 8 > stxdata;
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

	return status;
}

LtcCtrlStatus LTC6811Controller::rawWrite(WCmd cmd)
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
LtcCtrlStatus LTC6811Controller::rawRead(RCmd cmd, std::array < RdReg, CHAIN_SIZE > &data)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	std::array < uint8_t, 4 + CHAIN_SIZE * 8 > stxdata;
	std::array < uint8_t, 4 + CHAIN_SIZE * 8 > srxdata;
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
LtcCtrlStatus LTC6811Controller::rawRead(RCmd cmd, std::array < RdReg, CHAIN_SIZE > &data, std::array < PecStatus, CHAIN_SIZE > &pec_status)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	std::array < uint8_t, 4 + CHAIN_SIZE * 8 > stxdata;
	std::array < uint8_t, 4 + CHAIN_SIZE * 8 > srxdata;
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

void LTC6811Controller::wakeUp()
{
	uint8_t dummy = 0;
	cs.activate();
	SpiTxRequest request(hspi, &dummy, 1);
	SpiDmaController::spiRequestAndWait(request);
	cs.deactivate();
	osDelay(twake_full);
}

void LTC6811Controller::handleWatchDog()
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

PollStatus LTC6811Controller::pollAdcStatus()
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

LtcCtrlStatus LTC6811Controller::configure()
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	//std::array < Config, chain_size > configs_buff;
	//std::array < PecStatus, chain_size > pecs;

	wakeUp();
	rawWrite(CMD_WRCFGA, configs);
	//TODO: check config? for now i threw it out

	return status;
}

LtcCtrlStatus LTC6811Controller::readVoltages(std::array< std::array< float, 12 >, CHAIN_SIZE > &vol)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;
	std::array < std::array < PecStatus, CHAIN_SIZE >, 4 > pecs;
	std::array < std::array < CellVoltage, CHAIN_SIZE >, 4 > raw;

	wakeUp();
	rawWrite(CMD_ADCV(Mode::Normal, Discharge::NotPermited, Cell::All));

	osDelay(tadc);

	wakeUp();
	rawRead(CMD_RDCVA, raw[0], pecs[0]);
	wakeUp();
	rawRead(CMD_RDCVB, raw[1], pecs[1]);
	wakeUp();
	rawRead(CMD_RDCVC, raw[2], pecs[2]);
	wakeUp();
	rawRead(CMD_RDCVD, raw[3], pecs[3]);

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		for(size_t cell = 0; cell < 12; cell++)
		{
			size_t reg = cell / 3;
			size_t rcell = cell % 3;
			if(pecs[reg][ltc] == PecStatus::Ok)
				vol[ltc][cell] = convRawToU(raw[reg][ltc].cell[rcell].val);
			else
				vol[ltc][cell] = -1.f;
		}
	}

	return status;
}

LtcCtrlStatus LTC6811Controller::diagnose(std::array < LtcDiagnosisStatus, CHAIN_SIZE > &diag)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	return status;
}

LtcCtrlStatus LTC6811Controller::readGpioAndRef2(std::array< std::array< float, 6 >, CHAIN_SIZE > &aux)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;
	std::array < PecStatus, CHAIN_SIZE > pec_a;
	std::array < PecStatus, CHAIN_SIZE > pec_b;
	std::array < AuxilliaryVoltageA, CHAIN_SIZE > aux_a;
	std::array < AuxilliaryVoltageB, CHAIN_SIZE > aux_b;

	wakeUp();
	rawWrite(CMD_ADAX(Mode::Normal, Pin::All));

	osDelay(tadc);

	wakeUp();
	rawRead(CMD_RDAUXA, aux_a, pec_a);
	wakeUp();
	rawRead(CMD_RDAUXB,	aux_b, pec_b);

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
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

LtcCtrlStatus LTC6811Controller::setDischarge(std::array< std::array< bool, 12 >, CHAIN_SIZE > &dis)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;


	for(size_t i = 0; i < CHAIN_SIZE; i++)
	{
		configs[i].dcc1 	= dis[i][0];
		configs[i].dcc2 	= dis[i][1];
		configs[i].dcc3 	= dis[i][2];
		configs[i].dcc4 	= dis[i][3];
		configs[i].dcc5 	= dis[i][4];
		configs[i].dcc6 	= dis[i][5];
		configs[i].dcc7 	= dis[i][6];
		configs[i].dcc8 	= dis[i][7];
		configs[i].dcc9 	= dis[i][8];
		configs[i].dcc10 	= dis[i][9];
		configs[i].dcc11 	= dis[i][10];
		configs[i].dcc12 	= dis[i][11];
	}

	wakeUp();
	rawWrite(CMD_WRCFGA, configs);

	return status;
}

LtcCtrlStatus LTC6811Controller::readVoltages(std::array< std::atomic<float>, CELL_COUNT > &vol)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;
	std::array < std::array < PecStatus, CHAIN_SIZE >, 4 > pecs;
	std::array < std::array < CellVoltage, CHAIN_SIZE >, 4 > raw;

	wakeUp();
	rawWrite(CMD_ADCV(Mode::Normal, Discharge::NotPermited, Cell::All));

	osDelay(tadc);

	wakeUp();
	rawRead(CMD_RDCVA, raw[0], pecs[0]);
	wakeUp();
	rawRead(CMD_RDCVB, raw[1], pecs[1]);
	wakeUp();
	rawRead(CMD_RDCVC, raw[2], pecs[2]);
	wakeUp();
	rawRead(CMD_RDCVD, raw[3], pecs[3]);

	static constexpr std::array < size_t, 9 > cell_to_ltc_cell { 0, 1, 2, 3, 4, 6, 7, 8, 9 };
	for(size_t cell = 0; cell < CELL_COUNT; cell++)
	{
		size_t ltc = cell / 9;
		size_t ltc_cell = cell_to_ltc_cell[cell % 9];
		size_t reg = ltc_cell / 3;
		size_t reg_cell = ltc_cell % 3;

		if(pecs[reg][ltc] == PecStatus::Ok)
			vol[cell] = convRawToU(raw[reg][ltc].cell[reg_cell].val);
		else
			vol[cell] = -1.f;
	}

	return status;
}

LtcCtrlStatus LTC6811Controller::setDischarge(const std::array< std::atomic<bool>, CELL_COUNT > &dis)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;

	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc += 1)
	{
		size_t cell = ltc * 9;

		configs[ltc].dcc1 	= dis[cell + 0];
		configs[ltc].dcc2 	= dis[cell + 1];
		configs[ltc].dcc3 	= dis[cell + 2];
		configs[ltc].dcc4 	= dis[cell + 3];
		configs[ltc].dcc5 	= dis[cell + 4];
		//configs[ltc].dcc6 	= dis[cell + 4];
		configs[ltc].dcc7 	= dis[cell + 5];
		configs[ltc].dcc8 	= dis[cell + 6];
		configs[ltc].dcc9 	= dis[cell + 7];
		configs[ltc].dcc10 	= dis[cell + 8];
		//configs[ltc].dcc11 	= dis[cell + ];
		//configs[ltc].dcc12 	= dis[cell + ];
	}

	wakeUp();
	rawWrite(CMD_WRCFGA, configs);

	return status;
}

LtcCtrlStatus LTC6811Controller::readGpioTemp(std::array< std::atomic < float >, TEMP_COUNT > &temp)
{
	LtcCtrlStatus status = LtcCtrlStatus::Ok;
	std::array < std::array < PecStatus, CHAIN_SIZE >, 1 > pecs;
	std::array < std::array < AuxilliaryVoltage, CHAIN_SIZE >, 1 > aux;

	wakeUp();
	rawWrite(CMD_ADAX(Mode::Normal, Pin::All));

	osDelay(tadc);

	wakeUp();
	rawRead(CMD_RDAUXA, aux[0], pecs[0]);
	//wakeUp();
	//rawRead(CMD_RDAUXB,	aux[1], pecs[1]);

	for(size_t t = 0; t < TEMP_COUNT; t++)
	{
		size_t ltc = t / 3;
		size_t ltc_temp = t % 3;
		size_t reg = ltc_temp / 3;
		size_t reg_temp = ltc_temp % 3;

		if(pecs[reg][ltc] != PecStatus::Ok)
			temp.at(t) = -1.f;
		else
			temp.at(t) = convRawToGT(aux.at(reg).at(ltc).gpio[reg_temp].val);
	}

	return status;
}
