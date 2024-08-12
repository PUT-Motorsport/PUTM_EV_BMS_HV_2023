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
#include <optional>
#include <variant>

#include <Interfaces/LTC6811Cmd.hpp>
#include <Interfaces/LTC6811Regs.hpp>
#include <Config.hpp>
#include <Controllers/GpioController.hpp>

enum class LtcStatus
{
	Ok,
	PecError
};

class Ltc6811Controller
{
	public:
		Ltc6811Controller() = delete;
		Ltc6811Controller(GpioOut cs, SPI_HandleTypeDef &hspi);

		template < typename T >
		using RegArray 	= std::array < T, LtcConfig::CHAIN_SIZE >;
		template < typename T >
		using DataArray = std::array < T, LtcConfig::CHAIN_SIZE * 12 >;
		template < typename T >
		using GpioArray = std::array < T, LtcConfig::CHAIN_SIZE * 5 >;

		/*
		 * direct read
		 */
		template < Ltc6811::ReadRegisterGroup RdReg >
		LtcStatus rawRead(Ltc6811::RCmd cmd, RegArray < RdReg > *out, RegArray < LtcStatus > *out_pec);
		/*
		 * direct write overrides current mem
		 */
		template < Ltc6811::WriteReadRegisterGroup WrRdReg >
		LtcStatus rawWrite(Ltc6811::WCmd cmd, RegArray < WrRdReg> const *data);
		LtcStatus rawWrite(Ltc6811::WCmd cmd);

		LtcStatus configure();
		LtcStatus readVoltages(DataArray < float > *out);
		LtcStatus setDischarge(DataArray < bool > const *in);
		LtcStatus readGpio(GpioArray < float > *out);
		LtcStatus readStackVoltage(float *out);

		/*
		 * the ltc will timeout and will go into idle / sleep mode
		 * use every 2 sec in the case no valid command is scheduled
		 * to be send
		 */
		void handleWatchDog();
		void wakeUp();

		//LtcStatus pollAdcStatus();

	private:
		SPI_HandleTypeDef &hspi;
		GpioOut cs;

		//uint16_t(0x0fff) - 12bit mask
		constexpr static uint16_t vuv = std::min(uint16_t(0x0fff), uint16_t(std::round(ChecksConfig::CELL_MIN_VOLTAGE * 625.0 - 1.0)));
		constexpr static uint16_t vov = std::min(uint16_t(0x0fff), uint16_t(std::round(ChecksConfig::CELL_MAX_VOLTAGE * 625.0)));
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

		//convert soc reg to stack voltage
		constexpr float convRawToSU(uint16_t value)
		{
			return float(value * 20) * u_conv_coef;
		}

		RegArray <Ltc6811::Config > configs;
		//std::array < Communication, chain_size > comm_settings;

		constexpr static uint32_t twake_full = std::clamp(uint32_t(std::ceil(float(LtcConfig::CHAIN_SIZE) * twake_full_coef)), uint32_t(1), uint32_t(UINT32_MAX));
};

#endif /* INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_ */
