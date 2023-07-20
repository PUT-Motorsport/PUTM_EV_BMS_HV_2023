/*
 * ILocable.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */


#include "Interfaces/ILocable.hpp"

ILocable::ILocable()
{
	xSemaphore = xSemaphoreCreateMutexStatic( &xMutexBuffer );

	configASSERT( xSemaphore );
}

void ILocable::lock()
{
	xSemaphoreTake( xSemaphore, portMAX_DELAY );
}

void ILocable::lockFromIRQ(BaseType_t *pxHigherPriorityTaskWoken)
{
	xSemaphoreTakeFromISR( xSemaphore, pxHigherPriorityTaskWoken );
}


void ILocable::unlock()
{
	xSemaphoreGive( xSemaphore );
}

void ILocable::unlockFromIRQ(BaseType_t *pxHigherPriorityTaskWoken)
{
	xSemaphoreGiveFromISR( xSemaphore, pxHigherPriorityTaskWoken );
}


void usingLock(ILocable &locable, std::function<void()> action)
{
	locable.lock();
	action();
	locable.unlock();
}

void usingLockFromISR(ILocable &locable, std::function<void()> action, bool &yield)
{
	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	locable.lockFromIRQ(&pxHigherPriorityTaskWoken);
	yield = yield || pxHigherPriorityTaskWoken;
	action();
	locable.unlockFromIRQ(&pxHigherPriorityTaskWoken);
	yield = yield || pxHigherPriorityTaskWoken;
}


void usingLock(ILocable *locable, std::function<void()> action)
{
	locable->lock();
	action();
	locable->unlock();
}

void usingLockFromISR(ILocable *locable, std::function<void()> action, bool &yield)
{
	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	locable->lockFromIRQ(&pxHigherPriorityTaskWoken);
	yield = yield || pxHigherPriorityTaskWoken;
	action();
	locable->unlockFromIRQ(&pxHigherPriorityTaskWoken);
	yield = yield || pxHigherPriorityTaskWoken;
}
