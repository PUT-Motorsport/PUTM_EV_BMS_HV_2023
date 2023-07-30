/*
 * charger.hpp
 *
 *  Created on: Jul 20, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_CHARGER_HPP_
#define INC_PERYPHERIALMANAGERS_CHARGER_HPP_

#include "fdcan.h"
#include <array>
#include <span>

class ChargerCanTxMessage
{
	private:
		constexpr static FDCAN_HandleTypeDef &hfdcan = hfdcan2;
		constexpr static uint32_t CHARGER_TX_ID = 0x1806E5F4;
		std::array<uint8_t, 8> data;

		constexpr static FDCAN_TxHeaderTypeDef charger_transmit_header = []
		{
			FDCAN_TxHeaderTypeDef temp_header{};
			temp_header.Identifier = CHARGER_TX_ID;
			temp_header.IdType = FDCAN_EXTENDED_ID;
			temp_header.TxFrameType = FDCAN_DATA_FRAME;
			temp_header.DataLength = FDCAN_DLC_BYTES_8;
			temp_header.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
			temp_header.BitRateSwitch = FDCAN_BRS_OFF;
			temp_header.FDFormat = FDCAN_CLASSIC_CAN;
			temp_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			temp_header.MessageMarker = 0;
			return temp_header;
		}();

	public:
		constexpr ChargerCanTxMessage(float voltage, float current, bool enable)
			: data{
				  static_cast<uint8_t>((uint16_t)(voltage * 10) >> 8),
				  static_cast<uint8_t>((uint16_t)(voltage * 10)),
				  static_cast<uint8_t>((uint16_t)(current * 10) >> 8),
				  static_cast<uint8_t>((uint16_t)(current * 10)),
				  static_cast<uint8_t>(not enable),
				  0,
				  0,
				  0} { }

		HAL_StatusTypeDef send()
		{
			return HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan,
												 const_cast<FDCAN_TxHeaderTypeDef *>(&charger_transmit_header),
												 const_cast<uint8_t *>(data.begin()));
		}
};

class ChargerCanRxMessageHandler
{
	private:
		constexpr static FDCAN_HandleTypeDef &hfdcan = hfdcan2;
		constexpr static uint32_t CHARGER_RX_ID = 0x18ff50e5;

		std::array<uint8_t, 8> data{};
		float battery_read_voltage{};
		float battery_read_current{};
		bool hardware_fail{};
		bool over_temperature{};
		bool in_voltage_fail{};
		bool starting_state{};
		bool communication_state{};
		uint32_t last_recive_tick{};
		bool charger_time_out{};

		uint32_t canFifoMessageCount() const
		{
			return HAL_FDCAN_GetRxFifoFillLevel(&hfdcan, FDCAN_RX_FIFO0);
		}

		inline void processFrame()
		{
			FDCAN_RxHeaderTypeDef header{};
			auto status = HAL_FDCAN_GetRxMessage(&hfdcan, FDCAN_RX_FIFO0, &header, data.begin());

			if (CHARGER_RX_ID == header.Identifier and HAL_OK == status)
			{
				uint16_t voltage = ((uint16_t)(data[0]) << 8) | ((uint16_t)data[1]);
				uint16_t current = ((uint16_t)(data[2]) << 8) | ((uint16_t)data[3]);
				battery_read_voltage = voltage * 0.1f;
				battery_read_current = current * 0.1f;
				hardware_fail = data[4] & 0x01;
				over_temperature = data[4] & 0x02;
				in_voltage_fail = data[4] & 0x04;
				starting_state = data[4] & 0x08;
				communication_state = data[4] & 0x10;
				last_recive_tick = HAL_GetTick();
			}
		}

	public:
		inline void update()
		{
			while (canFifoMessageCount() not_eq 0)
			{
				processFrame();
			}
		}

		constexpr float getBatteryVoltage() const
		{
			return battery_read_voltage;
		}

		constexpr float getBatteryCurrent() const
		{
			return battery_read_current;
		}
};

#endif /* INC_PERYPHERIALMANAGERS_CHARGER_HPP_ */
