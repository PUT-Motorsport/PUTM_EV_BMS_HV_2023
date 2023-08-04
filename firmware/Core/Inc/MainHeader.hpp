/*
 * MainHeader.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: piotr
 */

#ifndef INC_MAINHEADER_HPP_
#define INC_MAINHEADER_HPP_

//#define PUTM_USE_CAN_FD

#include <main.h>
#include <cmsis_os.h>
#include <adc.h>
#include <dma.h>
#include <app_fatfs.h>
#include <fdcan.h>
#include <rtc.h>
#include <spi.h>
#include <tim.h>
#include <usb_device.h>
#include <gpio.h>
#include <FreeRTOS.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <fdcan.h>
#include <numeric>
#include <optional>
#include <queue.h>
#include <ranges>
#include <span>
#include <spi.h>
#include <task.h>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
// #include <PUTM_EV_CAN_LIBRARY/lib/can_interface.hpp>
#include <Config.hpp>
#include <StackData.hpp>
#include <PerypherialManagers/Utils.hpp>
#include <PerypherialManagers/CanUtils.hpp>
#include <PerypherialManagers/Gpio.hpp>
#include <PerypherialManagers/PEC15.hpp>
#include <Interfaces/StateErrorWarning.hpp>
#include <PerypherialManagers/Checks.hpp>
#include <PerypherialManagers/SpiDmaController.hpp>
#include <PerypherialManagers/ChargeBalanceController.hpp>
#include <PerypherialManagers/Charger.hpp>
#include <PerypherialManagers/PlausibilityChecker.hpp>
#include <Interfaces/LTC6811Regs.hpp>
#include <Interfaces/LTC6811Cmd.hpp>
#include <PerypherialManagers/LTC6811Controller.hpp>
#include <Interfaces/MCP356xCmd.hpp>
#include <Interfaces/MCP356xRegs.hpp>
#include <PerypherialManagers/MCP356xController.hpp>
#include <app_freertos.h>

#endif /* INC_MAINHEADER_HPP_ */
