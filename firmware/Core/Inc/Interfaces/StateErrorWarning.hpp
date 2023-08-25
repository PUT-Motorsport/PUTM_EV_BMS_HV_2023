/*
 * StateErrorWarning.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_INTERFACES_STATEERRORWARNING_HPP_
#define INC_INTERFACES_STATEERRORWARNING_HPP_

#include <array>
#include <main.h>
#include <optional>
#include <string_view>
#include <variant>

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
    MaintenancePlugNotConnected,
    _size
};

enum struct WarningsEnum : uint8_t
{
    BallanceError_100mV,
    BallanceError_200mV,
};

namespace Checks
{
    using namespace std::literals;

    constexpr static std::array ErrorNamesMap{
        // cell voltage
        "under_voltage"sv,
        "over_voltage"sv,
        "measurement_disconnected"sv,

        // Cell temperature
        "under_temperature"sv,
        "over_temperature"sv,
        "temperature_sensor_disconnected"sv,

        // Whole battery current sensor
        "over_current"sv,
        "current_sensor_disconnected"sv,

        // Whole battery voltage sensor
        "over_voltage_stack"sv,
        "under_voltage_stack"sv,
        "voltage_sensor_disconnected"sv,

        // Battery stack
        "maintenance_plug_not_connected"sv};

    using CriticalError = std::pair<CriticalErrorsEnum, size_t>; // cell number
    using OptionalError = std::optional<CriticalError>;
    using ErrorListElement = std::pair<Checks::CriticalError, bool>;
}
#endif /* INC_INTERFACES_STATEERRORWARNING_HPP_ */
