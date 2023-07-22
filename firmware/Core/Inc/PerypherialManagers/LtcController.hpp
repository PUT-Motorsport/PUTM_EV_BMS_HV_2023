/*
 * LtcSpiCommCtrl.hpp
 *
 *  Created on: 25 maj 2023
 *      Author: user
 */

#ifndef INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_
#define INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_

#include "PerypherialManagers/LTC6811Lib.hpp"
#include "PerypherialManagers/LTC6811CmdCodes.hpp"
#include "PerypherialManagers/PEC15.hpp"
#include "PerypherialManagers/SpiDmaManager.hpp"
#include "PerypherialManagers/Gpio.hpp"

#include <main.h>
#include <array>
#include <type_traits>
#include <math.h>
#include <algorithm>
#include <spi.h>

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

static constexpr size_t chain_size = 1;
static constexpr double undervoltage = 2.0;
static constexpr double overvoltage = 3.0;

class LtcController
{
	public:
		LtcController() = delete;
		LtcController(GpioOut gpio, SPI_HandleTypeDef* hspi);

		/*
		 * direct read
		 */
		template < class RdReg >
		LtcCtrlStatus rawRead(RCmd cmd, std::array < RdReg, chain_size > &data);

		template < class RdReg >
		LtcCtrlStatus rawRead(RCmd cmd, std::array < RdReg, chain_size > &data, std::array < PecStatus, chain_size > &pec_status);

		/*
		 * direct write overrides current mem
		 */
		template < class WrRdReg >
		LtcCtrlStatus rawWrite(WCmd cmd, std::array< WrRdReg, chain_size > const &data);
		LtcCtrlStatus rawWrite(WCmd cmd);

		LtcCtrlStatus configure();
		LtcCtrlStatus readVoltages(std::array< std::array< float, 12 >, chain_size > &vol);
		/*
		 * the ltc will timeout and will go into idle / sleep mode
		 * use every 2 sec in the case no valid command is scheduled
		 * to be send
		 */
		void handleWatchDog();
		void wakeUp();

		PollStatus pollAdcStatus();

	private:

		SPI_HandleTypeDef* hspi;
		GpioOut gpio;

		//uint16_t(0x0fff) - 12bit mask
		static constexpr uint16_t vuv = std::min(uint16_t(0x0fff), uint16_t(std::round(undervoltage * 625.0 - 1.0)));
		static constexpr uint16_t vov = std::min(uint16_t(0x0fff), uint16_t(std::round(undervoltage * 625.0)));

		std::array < LTC6811::Config, chain_size > configs;
		std::array < LTC6811::Communication, chain_size > comm_settings;

		bool lock_cs;

		struct Config
		{
			//twake in ms typ: 100us - 300us
			constexpr static inline float twake = 0.3f;
			constexpr static inline uint32_t twake_full = std::clamp(uint32_t(std::ceil(float(chain_size) * twake)), uint32_t(1), uint32_t(UINT32_MAX));
		};
};

#endif /* INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_ */
