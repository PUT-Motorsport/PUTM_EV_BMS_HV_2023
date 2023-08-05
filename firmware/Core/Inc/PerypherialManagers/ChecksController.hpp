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

#include <Interfaces/StateErrorWarning.hpp>

namespace Checks
{
    constexpr static float CELL_MAX_VOLTAGE = 4.175f;
    constexpr static float CELL_MIN_VOLTAGE = 3.0f;
    constexpr static float CELL_MAX_TEMPERATURE = 50.0f;
    constexpr static float CELL_MIN_TEMPERATURE = -20.0f;

    constexpr ErrorOrWarning underVoltage(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltc_data.voltages, [](const auto &cellVoltage)
                                         { return cellVoltage < CELL_MIN_VOLTAGE; });
        if (iter not_eq std::end(stackData.ltc_data.voltages))
        {
            return std::make_pair(CriticalErrorsEnum::UnderVoltage, std::distance(std::begin(stackData.ltc_data.voltages), iter));
        }
        return std::nullopt;
    }

    constexpr ErrorOrWarning overVoltage(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltc_data.voltages, [](const auto &cellVoltage)
                                         { return cellVoltage > CELL_MAX_VOLTAGE; });
        if (iter not_eq std::end(stackData.ltc_data.voltages))
        {
            return std::make_pair(CriticalErrorsEnum::OverVoltage, std::distance(std::begin(stackData.ltc_data.voltages), iter));
        }
        return std::nullopt;
    }

    constexpr ErrorOrWarning underTemperature(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltc_data.temp, [](const auto &cellTemperature)
                                         { return cellTemperature < CELL_MIN_TEMPERATURE; });
        if (iter not_eq std::end(stackData.ltc_data.temp))
        {
            return std::make_pair(CriticalErrorsEnum::UnderTemperature, std::distance(std::begin(stackData.ltc_data.temp), iter));
        }
        return std::nullopt;
    }

    constexpr ErrorOrWarning overTemperature(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltc_data.temp, [](const auto &cellTemperature)
                                         { return cellTemperature > CELL_MAX_TEMPERATURE; });

        if (iter not_eq std::end(stackData.ltc_data.temp))
        {
            return std::make_pair(CriticalErrorsEnum::OverTemperature, std::distance(std::begin(stackData.ltc_data.temp), iter));
        }
        return std::nullopt;
    }

}

#endif /* INC_PERYPHERIALMANAGERS_CHECKSCONTROLLER_HPP_ */
