/*
 * Config.hpp
 *
 *  Created on: 3 sie 2023
 *      Author: piotr
 */

#ifndef INC_INTERFACES_CONFIG_HPP_
#define INC_INTERFACES_CONFIG_HPP_

#include "main.h"

//ltc
static constexpr size_t chain_size = 15;
static constexpr float undervoltage = 2.f;
static constexpr float overvoltage = 4.f;

static constexpr size_t cell_count = chain_size * 9;
static constexpr size_t temp_count = chain_size * 3;

#endif /* INC_INTERFACES_CONFIG_HPP_ */
