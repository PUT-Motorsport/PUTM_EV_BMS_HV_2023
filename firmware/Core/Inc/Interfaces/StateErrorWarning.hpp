/*
 * StateErrorWarning.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_INTERFACES_STATEERRORWARNING_HPP_
#define INC_INTERFACES_STATEERRORWARNING_HPP_

#include "MainHeader.hpp"

enum struct CriticalErrorsEnum : uint8_t
{
    // cell voltage
    UnderVoltage,
    OverVoltage,
    MeasurementDisconnected,

    // Cell temperature
    UnderTemperature,
    OverTemperature,
    TemperatureSensorDisconnected,

    // Whole battery current sensor
    OverCurrent,
    CurrentSensorDisconnected,

    // Whole battery voltage sensor
    OverVoltageStack,
    UnderVoltageStack,
    VoltageSensorDisconnected,

    // Battery stack
    MaintenancePlugNotConnected
};

enum struct WarningsEnum : uint8_t
{
    BallanceError_100mV,
    BallanceError_200mV,
};

namespace CHECKS
{
    using CriticalError = std::pair<CriticalErrorsEnum, size_t>; // cell number
    using Warning = std::pair<WarningsEnum, size_t>;             // cell number
    using ErrorOrWarning = std::optional<std::variant<CriticalError, Warning>>;
}
#endif /* INC_INTERFACES_STATEERRORWARNING_HPP_ */
