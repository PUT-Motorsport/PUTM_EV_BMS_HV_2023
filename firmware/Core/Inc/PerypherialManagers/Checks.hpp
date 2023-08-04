/*
 * Checks.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_CHECKS_HPP_
#define INC_PERYPHERIALMANAGERS_CHECKS_HPP_

#include "Interfaces/StateErrorWarning.hpp"
#include "stackData.hpp"
#include <algorithm>
#include <cstdint>
#include <optional>
#include <ranges>
#include <utility>
#include <variant>

namespace CHECKS
{
    constexpr static float CELL_MAX_VOLTAGE = 4.175f;
    constexpr static float CELL_MIN_VOLTAGE = 3.0f;
    constexpr static float CELL_MAX_TEMPERATURE = 50.0f;
    constexpr static float CELL_MIN_TEMPERATURE = -20.0f;

    constexpr ErrorOrWarning underVoltage(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltcData.volt, [](const auto &cellVoltage)
                                         { return cellVoltage < CELL_MIN_VOLTAGE; });
        if (iter not_eq std::end(stackData.ltcData.volt))
        {
            return std::make_pair(CriticalErrorsEnum::UnderVoltage, std::distance(std::begin(stackData.ltcData.volt), iter));
        }
        return std::nullopt;
    }

    constexpr ErrorOrWarning overVoltage(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltcData.volt, [](const auto &cellVoltage)
                                         { return cellVoltage > CELL_MAX_VOLTAGE; });
        if (iter not_eq std::end(stackData.ltcData.volt))
        {
            return std::make_pair(CriticalErrorsEnum::OverVoltage, std::distance(std::begin(stackData.ltcData.volt), iter));
        }
    }

    constexpr ErrorOrWarning underTemperature(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltcData.temp, [](const auto &cellTemperature)
                                         { return cellTemperature < CELL_MIN_TEMPERATURE; });
        if (iter not_eq std::end(stackData.ltcData.temp))
        {
            return std::make_pair(CriticalErrorsEnum::UnderTemperature, std::distance(std::begin(stackData.ltcData.temp), iter));
        }
        return std::nullopt;
    }

    constexpr ErrorOrWarning overTemperature(const FullStackData &stackData)
    {
        auto iter = std::ranges::find_if(stackData.ltcData.temp, [](const auto &cellTemperature)
                                         { return cellTemperature > CELL_MAX_TEMPERATURE; });

        if (iter not_eq std::end(stackData.ltcData.temp))
        {
            return std::make_pair(CriticalErrorsEnum::OverTemperature, std::distance(std::begin(stackData.ltcData.temp), iter));
        }
        return std::nullopt;
    }

}

#endif /* INC_PERYPHERIALMANAGERS_CHECKS_HPP_ */
