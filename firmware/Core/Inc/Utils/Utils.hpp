/*
 * Utils.hpp
 *
 *  Created on: 2 sie 2023
 *      Author: piotr
 */

#ifndef INC_PERYPHERIALMANAGERS_UTILS_HPP_
#define INC_PERYPHERIALMANAGERS_UTILS_HPP_

#include <main.h>
#include <concepts>

// or operator for 16bit sized enums
template < typename T >
concept Enum = std::is_enum< T >::value;

template < Enum T >
constexpr static inline uint16_t operator | (uint16_t n, T e)
{
	return static_cast< uint16_t >(e) | n;
}

//template < Enum T >
//constexpr static inline uint8_t operator | (uint8_t n, T e)
//{
//	return static_cast<uint8_t>(e) | n;
//}

#endif /* INC_PERYPHERIALMANAGERS_UTILS_HPP_ */
