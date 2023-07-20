/*
 * LocableResource.hpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#ifndef INC_PERYPHERIALMANAGERS_LOCABLERESOURCE_HPP_
#define INC_PERYPHERIALMANAGERS_LOCABLERESOURCE_HPP_

#include "Interfaces/ILocable.hpp"

template < typename T >
class LocableResource : public ILocable
{
	public:
		T resource;
};

#endif /* INC_PERYPHERIALMANAGERS_LOCABLERESOURCE_HPP_ */
