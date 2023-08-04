/*
 * can_utils.cpp
 *
 *  Created on: Jul 22, 2023
 *      Author: jan
 */

#include "PerypherialManagers/CanUtils.hpp"
#include "main.h"

bool startCan(FDCAN_HandleTypeDef &hfdcan){

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
			HAL_FDCAN_ActivateNotification(&hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
		if (HAL_OK != can_notification_status)
		{
			return false;
		}

		const auto can_filter_config_status =
			HAL_FDCAN_ConfigFilter(&hfdcan, const_cast<FDCAN_FilterTypeDef *>(&sFilterConfig));

		if (HAL_OK != can_filter_config_status)
		{
			return false;
		}

		if (HAL_FDCAN_Start(&hfdcan) != HAL_OK)
		{
			return false;
		}
		return true;
}



uint32_t getCanFifoMessageCount(FDCAN_HandleTypeDef &hfdcan){
	return HAL_FDCAN_GetRxFifoFillLevel(&hfdcan, FDCAN_RX_FIFO0);
}
