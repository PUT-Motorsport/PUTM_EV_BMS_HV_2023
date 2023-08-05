/*
 * LtcSpiCommCtrl.hpp
 *
 *  Created on: 25 maj 2023
 *      Author: user
 */

#ifndef INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_
#define INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_

#include <main.h>
#include <array>
#include <atomic>
#include <cmath>
#include <algorithm>

#include <PerypherialManagers/GpioController.hpp>
#include <Interfaces/LTC6811Cmd.hpp>
#include <Interfaces/LTC6811Regs.hpp>
#include <Config.hpp>

enum struct PecStatus
{
	Ok,
	Error
};

enum struct PollStatus
{
	Busy,
	Done
};

enum struct LtcCtrlStatus
{
	Ok					= 0x00,
	Error				= 0x01,
	PecError			= 0x02,
	RegValMismatchError = 0x03
};

enum struct LtcDiagnosisStatus
{
	Passed,
	Warning,
	Failed
};

class LTC6811Controller
{
	public:
		LTC6811Controller() = delete;
		LTC6811Controller(GpioOut cs, SPI_HandleTypeDef &hspi);

		/*
		 * direct read
		 */
		template < LTC6811::ReadRegisterGroup RdReg >
		LtcCtrlStatus rawRead(LTC6811::RCmd cmd, std::array < RdReg, Ltc::CHAIN_SIZE > &data);

		template < LTC6811::ReadRegisterGroup RdReg >
		LtcCtrlStatus rawRead(LTC6811::RCmd cmd, std::array < RdReg, Ltc::CHAIN_SIZE > &data, std::array < PecStatus, Ltc::CHAIN_SIZE > &pec_status);

		/*
		 * direct write overrides current mem
		 */
		template < LTC6811::WriteReadRegisterGroup WrRdReg >
		LtcCtrlStatus rawWrite(LTC6811::WCmd cmd, std::array< WrRdReg, Ltc::CHAIN_SIZE > const &data);
		LtcCtrlStatus rawWrite(LTC6811::WCmd cmd);

		LtcCtrlStatus configure();
		LtcCtrlStatus readVoltages(std::array< std::array< float, 12 >, Ltc::CHAIN_SIZE > &vol);
		LtcCtrlStatus diagnose(std::array < LtcDiagnosisStatus, Ltc::CHAIN_SIZE > &diag);
		LtcCtrlStatus readGpioAndRef2(std::array< std::array< float, 6 >, Ltc::CHAIN_SIZE > &aux);
		LtcCtrlStatus setDischarge(std::array< std::array< bool, 12 >, Ltc::CHAIN_SIZE > &dis);

		//atomic versions
		LtcCtrlStatus readVoltages(std::array< std::atomic<float>, Ltc::CELL_COUNT > &vol);
		//LtcCtrlStatus diagnose(std::array < LtcDiagnosisStatus, Ltc::CHAIN_SIZE > &diag);
		//LtcCtrlStatus readGpioAndRef2(std::array< std::array< float, 6 >, Ltc::CHAIN_SIZE > &aux);
		LtcCtrlStatus setDischarge(const std::array< std::atomic<bool>, Ltc::CELL_COUNT > &dis);
		LtcCtrlStatus readGpioTemp(std::array< std::atomic < float >, Ltc::TEMP_COUNT > &temp);
		/*
		 * the ltc will timeout and will go into idle / sleep mode
		 * use every 2 sec in the case no valid command is scheduled
		 * to be send
		 */
		void handleWatchDog();
		void wakeUp();

		PollStatus pollAdcStatus();

	private:
		SPI_HandleTypeDef &hspi;
		GpioOut cs;

		//uint16_t(0x0fff) - 12bit mask
		constexpr static uint16_t vuv = std::min(uint16_t(0x0fff), uint16_t(std::round(Ltc::UNDERVOLTAGE * 625.0 - 1.0)));
		constexpr static uint16_t vov = std::min(uint16_t(0x0fff), uint16_t(std::round(Ltc::UNDERVOLTAGE * 625.0)));
		constexpr static float u_conv_coef = 0.000'1f;
		constexpr static float t_conv_coef = 0.000'1f / 0.007'5f;
		constexpr static float twake_full_coef = 0.2f;
		constexpr static size_t tadc = 15;

		// convert ADC to cell voltage returns in [V]
		constexpr float convRawToU(uint16_t value)
		{
			return float(value) * u_conv_coef;
		}

		// internal die temperature returns in [*C]
		constexpr float convRawToT(uint16_t value)
		{
			return float(value) * t_conv_coef - 273.f;
		}

		// convert gpio readings to temp
		constexpr float convRawToGT(uint16_t value)
		{
			return float(value) * 1.f;
		}

		std::array < LTC6811::Config, Ltc::CHAIN_SIZE > configs;
		//std::array < Communication, chain_size > comm_settings;

		constexpr static uint32_t twake_full = std::clamp(uint32_t(std::ceil(float(Ltc::CHAIN_SIZE) * twake_full_coef)), uint32_t(1), uint32_t(UINT32_MAX));
};

#endif /* INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_ */
