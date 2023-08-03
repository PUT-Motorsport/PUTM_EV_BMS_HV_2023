/*
 * can_utils.hpp
 *
 *  Created on: Jul 22, 2023
 *      Author: jan
 */

#ifndef INC_CAN_UTILS_HPP_
#define INC_CAN_UTILS_HPP_

#include "main.h"

bool startCan(FDCAN_HandleTypeDef &hfdcan);

uint32_t get_can_fifo_message_count(FDCAN_HandleTypeDef &hfdcan);


#endif /* INC_CAN_UTILS_HPP_ */
