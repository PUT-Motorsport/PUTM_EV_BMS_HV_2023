/*
 * ChargerCANManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: piotr
 */

#include "app_freertos.h"
#include "PerypherialManagers/Charger.hpp"
#include "main.h"
#include "can_utils.hpp"

extern FDCAN_HandleTypeDef hfdcan2;

void vChargerCANManagerTask(void *argument)
{
	startCan(hfdcan2);
	bool charging_enable{false};
	float charge_voltage = 135.0f * 4.15f;
	float charge_current = 2.0f;
	ChargerCanRxMessageHandler charger_rx{};

	while (true)
	{
		bool charger_connected = not HAL_GPIO_ReadPin(CHARGER_DETECT_GPIO_Port, CHARGER_DETECT_Pin);
		if(charger_connected){
			osDelay(100);
			charger_rx.update();
			ChargerCanTxMessage frame{charge_voltage, charge_current, charging_enable};
			frame.send();
		}
		else {
			osDelay(3000);
		}

	}
}




