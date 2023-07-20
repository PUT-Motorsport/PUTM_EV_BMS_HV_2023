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

template < size_t chain_size >
class LTCController
{
	public:
		LTCController() = delete;
		LTCController(GpioOut gpio, SPI_HandleTypeDef* hspi);

		/*
		 * direct read
		 */
		template < class RdReg >
		HAL_StatusTypeDef rawRead(RCmd cmd, std::array < RdReg, chain_size > &data);

		template < class RdReg >
		HAL_StatusTypeDef rawRead(RCmd cmd, std::array < RdReg, chain_size > &data, std::array < PecStatus, chain_size > &pec_status);

		/*
		 * direct write overrides current mem
		 */
		template < class WrRdReg >
		HAL_StatusTypeDef rawWrite(WCmd cmd, std::array< WrRdReg, chain_size > const &data);
		HAL_StatusTypeDef rawWrite(WCmd cmd);

		void wakeUp();
		/*
		 * the ltc will timeout and will go into idle / sleep mode
		 * use every 2 sec in the case no valid command is scheduled
		 * to be send
		 */
		void handleWatchDog();

	private:

		SPI_HandleTypeDef* hspi;
		GpioOut gpio;

		bool lock_cs;

		struct Config
		{
			//twake in ms typ: 100us - 300us
			constexpr static inline float twake = 0.3f;
			constexpr static inline uint32_t twake_full = std::clamp(uint32_t(std::ceil(float(chain_size) * twake)), uint32_t(1), uint32_t(UINT32_MAX));
		};
};

#endif /* INC_PUTM_LTC_6811_LTC6804_LIB_LIB_LTCSPICOMMCTRL_HPP_ */
