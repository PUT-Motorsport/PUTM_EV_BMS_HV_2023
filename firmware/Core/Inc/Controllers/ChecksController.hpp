/*
 * Checks.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_CONTROLLERS_CHECKSCONTROLLER_HPP_
#define INC_CONTROLLERS_CHECKSCONTROLLER_HPP_

#include <algorithm>
#include <main.h>

#include <Config.hpp>
#include <Interfaces/StateErrorWarning.hpp>
#include <StackData.hpp>

namespace Checks
{

    static OptionalError underVoltage(const FullStackData &stackData)
    {
        static int32_t error_cntr{0};
        auto iter = std::ranges::find_if(stackData.ltc.voltages, [](const auto &cellVoltage)
                                         { return cellVoltage < ChecksConfig::CELL_MIN_VOLTAGE; });

        if (iter not_eq std::end(stackData.ltc.voltages))
        {
            ++error_cntr;
        }
        else if (error_cntr > 0)
        {
            --error_cntr;
        }

        if (error_cntr > ChecksConfig::VOLTAGE_ERROR_COUNT_MAX and iter not_eq std::end(stackData.ltc.voltages))
        {
            return std::make_pair(CriticalErrorsEnum::UnderVoltage, std::distance(std::begin(stackData.ltc.voltages), iter));
        }
        return std::nullopt;
    }

    static OptionalError overVoltage(const FullStackData &stackData)
    {
        static int32_t error_cntr{0};

        int32_t now_tick = stackData.time.tick;
        int32_t dis_off_tick = stackData.charger.balance_disable_tick;

        if (stackData.charger.balance_enable or (now_tick < 10'000 + dis_off_tick ))
        {
            return std::nullopt;
        }

        auto iter = std::ranges::find_if(stackData.ltc.voltages, [](const auto &cellVoltage)
                                         { return cellVoltage > ChecksConfig::CELL_MAX_VOLTAGE; });

        if (iter not_eq std::end(stackData.ltc.voltages))
        {
            ++error_cntr;
        }
        else if (error_cntr > 0)
        {
            --error_cntr;
        }

        if (error_cntr > ChecksConfig::VOLTAGE_ERROR_COUNT_MAX and iter not_eq std::end(stackData.ltc.voltages))
        {
            return std::make_pair(CriticalErrorsEnum::OverVoltage, std::distance(std::begin(stackData.ltc.voltages), iter));
        }
        return std::nullopt;
    }

    static OptionalError underTemperature(const FullStackData &stackData)
    {
        static int32_t error_cntr{0};
        auto iter = std::ranges::find_if(stackData.ltc.temp_C, [](const auto &cellTemperature)
                                         { return cellTemperature < ChecksConfig::CELL_MIN_TEMPERATURE; });
        if (iter not_eq std::end(stackData.ltc.temp_C))
        {
            ++error_cntr;
        }
        else if (error_cntr > 0)
        {
            --error_cntr;
        }

        if (error_cntr > ChecksConfig::TEMP_ERROR_COUNT_MAX and iter not_eq std::end(stackData.ltc.voltages))
        {
            return std::make_pair(CriticalErrorsEnum::UnderTemperature, std::distance(std::begin(stackData.ltc.temp_C), iter));
        }
        return std::nullopt;
    }

    static OptionalError overTemperature(const FullStackData &stackData)
    {
        static int32_t error_cntr{0};
        auto iter = std::ranges::find_if(stackData.ltc.temp_C, [](const auto &cellTemperature)
                                         { return cellTemperature > ChecksConfig::CELL_MAX_TEMPERATURE; });

        if (iter not_eq std::end(stackData.ltc.temp_C))
        {
            ++error_cntr;
        }
        else if (error_cntr > 0)
        {
            --error_cntr;
        }

        if (error_cntr > ChecksConfig::TEMP_ERROR_COUNT_MAX and iter not_eq std::end(stackData.ltc.voltages))
        {
            return std::make_pair(CriticalErrorsEnum::OverTemperature, std::distance(std::begin(stackData.ltc.temp_C), iter));
        }
        return std::nullopt;
    }

    static OptionalError overCurrent(const FullStackData &stackData)
    {
        static int32_t error_cntr{0};
        bool overcurrent = std::abs(stackData.external.acu_curr) > ChecksConfig::BATTERY_MAX_CURRENT;
        bool disconnect = std::abs(stackData.external.acu_curr) > ChecksConfig::BATTERY_SENSOR_DISCONNECT;
        if (overcurrent and not disconnect)
        {
            ++error_cntr;
        }
        else if (error_cntr > 0)
        {
            --error_cntr;
        }

        if (error_cntr > ChecksConfig::CURRENT_ERROR_COUNT_MAX)
        {
            return std::make_pair(CriticalErrorsEnum::OverCurrent, 0);
        }
        return std::nullopt;
    }

    static OptionalError CurrentSensorDisconnect(const FullStackData &stackData)
    {
        static int32_t error_cntr{0};
        //bool disconnect = std::abs(stackData.external.acu_curr) > ChecksConfig::BATTERY_MAX_CURRENT;
        bool disconnect = std::abs(stackData.external.isens_ref) < 2.0f;// ChecksConfig::BATTERY_MAX_CURRENT;
        if (disconnect)
        {
            ++error_cntr;
        }
        else if (error_cntr > 0)
        {
            --error_cntr;
        }
        if (error_cntr > ChecksConfig::CURRENT_ERROR_COUNT_MAX)
        {
            return std::make_pair(CriticalErrorsEnum::CurrentSensorDisconnected, 0);
        }
        return std::nullopt;
    }

}

#endif /* INC_CONTROLLERS_CHECKSCONTROLLER_HPP_ */
