/*
 * ILocable.hpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#ifndef INC_INTERFACES_ILOCABLE_HPP_
#define INC_INTERFACES_ILOCABLE_HPP_

#include "FreeRTOS.h"
#include "projdefs.h"
#include "semphr.h"
#include <functional>

class ILocable
{
	public:
		ILocable();

		void lock();
		void lockFromIRQ(BaseType_t *pxHigherPriorityTaskWoken);
		void unlock();
		void unlockFromIRQ(BaseType_t *pxHigherPriorityTaskWoken);

		virtual ~ILocable() = default;
	private:
		SemaphoreHandle_t xSemaphore = NULL;
		StaticSemaphore_t xMutexBuffer;
};

void usingLock(ILocable &locable, std::function<void()> action);
void usingLockFromISR(ILocable &locable, std::function<void()> action, bool &yield);

void usingLock(ILocable *locable, std::function<void()> action);
void usingLockFromISR(ILocable *locable, std::function<void()> action, bool &yield);

#endif /* INC_INTERFACES_ILOCABLE_HPP_ */
