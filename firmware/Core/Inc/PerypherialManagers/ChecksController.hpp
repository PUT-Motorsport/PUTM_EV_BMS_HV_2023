/*
 * Checks.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_CHECKSCONTROLLER_HPP_
#define INC_PERYPHERIALMANAGERS_CHECKSCONTROLLER_HPP_

#include <main.h>
#include <algorithm>

#include <Config.hpp>
#include <Interfaces/StateErrorWarning.hpp>

namespace Checks
{
    constexpr ErrorOrWarning underVoltage(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltc_data.voltages, [](const auto &cellVoltage)
                                         { return cellVoltage < ChecksConfig::CELL_MIN_VOLTAGE; });
        if (iter not_eq std::end(stackData.ltc_data.voltages))
        {
            return std::make_pair(CriticalErrorsEnum::UnderVoltage, std::distance(std::begin(stackData.ltc_data.voltages), iter));
        }
        return std::nullopt;
    }

    constexpr ErrorOrWarning overVoltage(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltc_data.voltages, [](const auto &cellVoltage)
                                         { return cellVoltage > ChecksConfig::CELL_MAX_VOLTAGE; });
        if (iter not_eq std::end(stackData.ltc_data.voltages))
        {
            return std::make_pair(CriticalErrorsEnum::OverVoltage, std::distance(std::begin(stackData.ltc_data.voltages), iter));
        }
        return std::nullopt;
    }

    constexpr ErrorOrWarning underTemperature(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltc_data.temp, [](const auto &cellTemperature)
                                         { return cellTemperature < ChecksConfig::CELL_MIN_TEMPERATURE; });
        if (iter not_eq std::end(stackData.ltc_data.temp))
        {
            return std::make_pair(CriticalErrorsEnum::UnderTemperature, std::distance(std::begin(stackData.ltc_data.temp), iter));
        }
        return std::nullopt;
    }

    constexpr ErrorOrWarning overTemperature(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltc_data.temp, [](const auto &cellTemperature)
                                         { return cellTemperature > ChecksConfig::CELL_MAX_TEMPERATURE; });

        if (iter not_eq std::end(stackData.ltc_data.temp))
        {
            return std::make_pair(CriticalErrorsEnum::OverTemperature, std::distance(std::begin(stackData.ltc_data.temp), iter));
        }
        return std::nullopt;
    }

    inline ErrorOrWarning overCurrent(const FullStackData &stackData){
    	bool overcurrent = std::abs(stackData.external_data.acu_curr) > ChecksConfig::BATTERY_MAX_CURRENT;
    	bool disconnect = std::abs(stackData.external_data.acu_curr) > ChecksConfig::BATTERY_MAX_CURRENT;
    	if(overcurrent and not disconnect){
    		return std::make_pair(CriticalErrorsEnum::OverCurrent, 0);
    	}
    	return std::nullopt;
    }

    inline ErrorOrWarning CurrentSensorDisconnect(const FullStackData &stackData){
    	bool disconnect = std::abs(stackData.external_data.acu_curr) > ChecksConfig::BATTERY_MAX_CURRENT;
    	if(disconnect){
    		return std::make_pair(CriticalErrorsEnum::CurrentSensorDisconnected, 0);
    	}
    	return std::nullopt;
    }


}

#endif /* INC_PERYPHERIALMANAGERS_CHECKSCONTROLLER_HPP_ */
