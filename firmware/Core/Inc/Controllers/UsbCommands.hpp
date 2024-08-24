/*
 * UsbCommands.hpp
 *
 *  Created on: Aug 22, 2023
 *      Author: jan
 */

#ifndef INC_CONTROLLERS_USBCOMMANDS_HPP_
#define INC_CONTROLLERS_USBCOMMANDS_HPP_

#include <algorithm>
#include <array>
#include <optional>
#include <span>
#include <string_view>
#include <utility>

enum struct Command_type
{
	CommunicationToggle,
	CommunicationTest,
    StartCharging,
    StopCharging,
    StartBalance,
    StopBalance,
    SetChargeCurrent_1A,
    SetChargeCurrent_2A,
    SetChargeCurrent_4A,
    SetChargeCurrent_8A,
    SetChargeCurrent_12A,
    _size,
};

class BMS_command_parser
{
    constexpr static std::array<std::pair<std::string_view, Command_type>, static_cast<size_t>(Command_type::_size)>
	commands =
	{
		std::make_pair("!C-CC@", Command_type::CommunicationToggle),
		std::make_pair("!C-CT@", Command_type::CommunicationTest),
		std::make_pair("!C-ON@", Command_type::StartCharging),
		std::make_pair("!C-OF@", Command_type::StopCharging),
		std::make_pair("!B-ON@", Command_type::StartBalance),
		std::make_pair("!B-OF@", Command_type::StopBalance),
		std::make_pair("!I-1A@", Command_type::SetChargeCurrent_1A),
		std::make_pair("!I-2A@", Command_type::SetChargeCurrent_2A),
		std::make_pair("!I-4A@", Command_type::SetChargeCurrent_4A),
		std::make_pair("!I-8A@", Command_type::SetChargeCurrent_8A),
		std::make_pair("!I-12@", Command_type::SetChargeCurrent_12A)
	};

    constexpr std::optional<Command_type> parse_command(std::string_view command) const noexcept
    {
        for (auto const &[cmd, type] : commands)
        {
            if (command == cmd)
            {
                return type;
            }
        }
        return std::nullopt;
    }

public:
    BMS_command_parser() = default;

    template <typename T>
    constexpr std::optional<Command_type> parse(std::span<uint8_t> buff, T &write_index)
    {
        const auto start_iter = std::find(buff.begin(), buff.end(), '!');
        const auto end_iter = std::find(buff.begin(), buff.end(), '@');
        const size_t length = std::distance(start_iter, end_iter); // without '@' and '!'

        // not all data is available
        if (end_iter == buff.end())
        {
            return std::nullopt;
        }

        // incorrect command
//        if (start_iter == buff.end())
//        {
//            write_index = 0;
//            std::fill(buff.begin(), buff.end(), 0);
//            return std::nullopt;
//        }

        // command found
        std::string_view command{reinterpret_cast<char *>(buff.data() + std::distance(buff.begin(), start_iter)),
                                 length + 1};

        const auto res = parse_command(command);

        // clear buffer
        write_index = 0;
        std::fill(start_iter, end_iter + 1, 0);
        return res;
    }
};


#endif /* INC_CONTROLLERS_USBCOMMANDS_HPP_ */
