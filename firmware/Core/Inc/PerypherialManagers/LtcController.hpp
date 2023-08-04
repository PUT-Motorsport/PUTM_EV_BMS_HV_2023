/*
 * LtcSpiCommCtrl.hpp
 *
 *  Created on: 25 maj 2023
 *      Author: user
 */

#ifndef INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_
#define INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_

#include "PerypherialManagers/LTC6811CmdCodes.hpp"
#include "PerypherialManagers/LTC6811Regs.hpp"
#include "PerypherialManagers/PEC15.hpp"
#include "PerypherialManagers/Gpio.hpp"
#include "Config.hpp"

#include <main.h>
#include <array>
#include <type_traits>
#include <math.h>
#include <PerypherialManagers/SpiDmaController.hpp>
#include <algorithm>
#include <spi.h>
#include <atomic>

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

class LtcController
{
	public:
		LtcController() = delete;
		LtcController(GpioOut cs, SPI_HandleTypeDef &hspi);

		/*
		 * direct read
		 */
		template < LTC6811::ReadRegisterGroup RdReg >
		LtcCtrlStatus rawRead(LTC6811::RCmd cmd, std::array < RdReg, chain_size > &data);

		template < LTC6811::ReadRegisterGroup RdReg >
		LtcCtrlStatus rawRead(LTC6811::RCmd cmd, std::array < RdReg, chain_size > &data, std::array < PecStatus, chain_size > &pec_status);

		/*
		 * direct write overrides current mem
		 */
		template < LTC6811::WriteReadRegisterGroup WrRdReg >
		LtcCtrlStatus rawWrite(LTC6811::WCmd cmd, std::array< WrRdReg, chain_size > const &data);
		LtcCtrlStatus rawWrite(LTC6811::WCmd cmd);

		LtcCtrlStatus configure();
		LtcCtrlStatus readVoltages(std::array< std::array< float, 12 >, chain_size > &vol);
		LtcCtrlStatus diagnose(std::array < LtcDiagnosisStatus, chain_size > &diag);
		LtcCtrlStatus readGpioAndRef2(std::array< std::array< float, 6 >, chain_size > &aux);
		LtcCtrlStatus setDischarge(std::array< std::array< bool, 12 >, chain_size > &dis);

		//atomic versions
		LtcCtrlStatus readVoltages(std::array< std::atomic<float>, cell_count > &vol);
		//LtcCtrlStatus diagnose(std::array < LtcDiagnosisStatus, chain_size > &diag);
		//LtcCtrlStatus readGpioAndRef2(std::array< std::array< float, 6 >, chain_size > &aux);
		LtcCtrlStatus setDischarge(std::array< std::atomic<float>, cell_count > &dis);
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
		constexpr static uint16_t vuv = std::min(uint16_t(0x0fff), uint16_t(std::round(undervoltage * 625.0 - 1.0)));
		constexpr static uint16_t vov = std::min(uint16_t(0x0fff), uint16_t(std::round(undervoltage * 625.0)));
		constexpr static float u_conv_coef = 0.000'1f;
		constexpr static float g_conv_coef = 0.000'1f;
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
			return float(value) * g_conv_coef;
		}

		std::array < LTC6811::Config, chain_size > configs;
		//std::array < Communication, chain_size > comm_settings;

		constexpr static uint32_t twake_full = std::clamp(uint32_t(std::ceil(float(chain_size) * twake_full_coef)), uint32_t(1), uint32_t(UINT32_MAX));
};

#endif /* INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_ */
