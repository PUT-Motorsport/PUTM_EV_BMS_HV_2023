/*
 * UsbUtils.hpp
 *
 *  Created on: Aug 19, 2023
 *      Author: jan
 */

#ifndef INC_UTILS_USBUTILS_HPP_
#define INC_UTILS_USBUTILS_HPP_

#include <stdint.h>

struct UsbDataStruct
{
	uint8_t new_data;
	uint8_t ctr;
	uint8_t len;
	uint8_t buff[64];
};


#endif /* INC_UTILS_USBUTILS_HPP_ */
