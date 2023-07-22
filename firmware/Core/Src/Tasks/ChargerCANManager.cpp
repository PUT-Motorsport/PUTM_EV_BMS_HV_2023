/*
 * ChargerCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: piotr
 */

#include "app_freertos.h"
#include "PerypherialManagers/Charger.hpp"
#include "main.h"

extern FDCAN_HandleTypeDef hfdcan2;
void startCanCharger();

void vChargerCANManagerTask(void *argument)
{
	startCanCharger();
	// FIXME to debug CAN communication
	bool charger_connected{false};
	bool charging_enable{false};
	float charge_voltage = 135.0f * 4.15f;
	float charge_current = 2.0f;
	ChargerCanRxMessageHandler charger_rx;

	while (true)
	{
		osDelay(100);
		charger_rx.update();
		ChargerCanTxMessage frame{charge_voltage, charge_current, charging_enable};
		frame.send();
	}
}



void startCanCharger(){

	constexpr static FDCAN_FilterTypeDef sFilterConfig = []
		{
			FDCAN_FilterTypeDef temp{};
			temp.IdType = FDCAN_STANDARD_ID;
			temp.FilterIndex = 0;
			temp.FilterType = FDCAN_FILTER_MASK;
			temp.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
			temp.FilterID1 = 0;
			temp.FilterID2 = 0;
			return temp;
		}();

		const auto can_notification_status =
			HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
		if (HAL_OK != can_notification_status)
		{
			Error_Handler();
		}

		const auto can_filter_config_status =
			HAL_FDCAN_ConfigFilter(&hfdcan2, const_cast<FDCAN_FilterTypeDef *>(&sFilterConfig));

		if (HAL_OK != can_filter_config_status)
		{
			Error_Handler();
		}

		if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
		{
			Error_Handler();
		}

}
