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
    inline static ErrorOrWarning underVoltage(const FullStackData &stackData)
    {
    	static std::array<int8_t, LtcConfig::CELL_COUNT> undervoltage_error_array{};

    	for(size_t i = 0; i < LtcConfig::CELL_COUNT; ++i){

    		const float cell_voltage = stackData.ltc_data.voltages[i];
    		const bool under_voltage = cell_voltage < ChecksConfig::CELL_MIN_VOLTAGE;
    		int8_t& error_count = undervoltage_error_array[i];

    		if(under_voltage){
    			error_count++;
    		}
    		else if(error_count not_eq 0){
    			error_count--;
    		}
    	}

        auto iter = std::ranges::find_if(undervoltage_error_array, [](const auto &error_count)
                                         { return error_count > 25; });

        if (iter not_eq std::end(undervoltage_error_array))
        {
            return std::make_pair(CriticalErrorsEnum::UnderVoltage, std::distance(undervoltage_error_array.begin(), iter));
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
        auto iter = std::ranges::find_if(stackData.ltc_data.temp_C, [](const auto &cellTemperature)
                                         { return cellTemperature < ChecksConfig::CELL_MIN_TEMPERATURE; });
        if (iter not_eq std::end(stackData.ltc_data.temp_C))
        {
            return std::make_pair(CriticalErrorsEnum::UnderTemperature, std::distance(std::begin(stackData.ltc_data.temp_C), iter));
        }
        return std::nullopt;
    }

    constexpr ErrorOrWarning overTemperature(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltc_data.temp_C, [](const auto &cellTemperature)
                                         { return cellTemperature > ChecksConfig::CELL_MAX_TEMPERATURE; });

        if (iter not_eq std::end(stackData.ltc_data.temp_C))
        {
            return std::make_pair(CriticalErrorsEnum::OverTemperature, std::distance(std::begin(stackData.ltc_data.temp_C), iter));
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
