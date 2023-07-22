/*
 * SpiDmaManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include "PerypherialManagers/SpiDmaManager.hpp"
#include "task.h"

static constexpr uint32_t bit31 = (1 << 31);

void SpiDmaManager::initSpiDmaManager()
{
	xTxRxQueue1 = xQueueCreateStatic( queueSize, txRxStructSize, ucTxRxQueue1StorageArea, &xStaticTxRxQueue1 );
	xTxRxQueue2 = xQueueCreateStatic( queueSize, txRxStructSize, ucTxRxQueue2StorageArea, &xStaticTxRxQueue2 );
	xTxRxQueue3 = xQueueCreateStatic( queueSize, txRxStructSize, ucTxRxQueue3StorageArea, &xStaticTxRxQueue3 );
}

void SpiDmaManager::spiRequestAndWait(SpiDmaHandle handle)
{
	addRequest(handle);
	waitForNotify();
}

QueueHandle_t SpiDmaManager::assignQueue(SPI_HandleTypeDef * hspi)
{
	if(hspi == &hspi1) return xTxRxQueue1;
	if(hspi == &hspi2) return xTxRxQueue2;
	if(hspi == &hspi3) return xTxRxQueue3;

	return nullptr;
}

void SpiDmaManager::addRequest(SpiDmaHandle rSpiDmaHandle)
{
	QueueHandle_t queueHandle = assignQueue(rSpiDmaHandle.hspi);
	//TODO: ???
	if(queueHandle == nullptr); //Error

	xQueueSendToBack(queueHandle, &rSpiDmaHandle, portMAX_DELAY);
	if(uxQueueMessagesWaiting(queueHandle) == 1)
	{
		rSpiDmaHandle.cs->activate();
		if(rSpiDmaHandle.pTxData != nullptr && rSpiDmaHandle.pRxData == nullptr)
			HAL_SPI_Transmit_DMA(rSpiDmaHandle.hspi, rSpiDmaHandle.pTxData, rSpiDmaHandle.dataSize);
		else if(rSpiDmaHandle.pRxData != nullptr && rSpiDmaHandle.pTxData == nullptr)
			HAL_SPI_Receive_DMA(rSpiDmaHandle.hspi, rSpiDmaHandle.pRxData, rSpiDmaHandle.dataSize);
		else
			HAL_SPI_TransmitReceive_DMA(rSpiDmaHandle.hspi, rSpiDmaHandle.pTxData, rSpiDmaHandle.pRxData, rSpiDmaHandle.dataSize);
	}
}

void SpiDmaManager::waitForNotify()
{
	uint32_t pulNotificationValue = 0;
	while(true)
	{
		xTaskNotifyWait(0, bit31, &pulNotificationValue, portMAX_DELAY);
		if (pulNotificationValue & bit31) break;
	}
}

inline void HAL_SPI_Handle(SPI_HandleTypeDef * hspi)
{
	SpiDmaHandle spiDmaHandle = { 0 };
	QueueHandle_t queueHandle = SpiDmaManager::assignQueue(hspi);
	//TODO: ???
	if(queueHandle == nullptr); //Error
	if(xQueueIsQueueEmptyFromISR(queueHandle) == pdTRUE); //Error

	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	bool yield = false;

	xQueueReceiveFromISR(queueHandle, &spiDmaHandle, &pxHigherPriorityTaskWoken);
	yield = yield || pxHigherPriorityTaskWoken;

	spiDmaHandle.cs->deactivate();

	xTaskNotifyFromISR(spiDmaHandle.taskToNotify, bit31, eSetBits, &pxHigherPriorityTaskWoken);
	yield = yield || pxHigherPriorityTaskWoken;

	if(yield) taskYIELD();
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * hspi)
{
	HAL_SPI_Handle(hspi);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi)
{
	HAL_SPI_Handle(hspi);
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	HAL_SPI_Handle(hspi);
}
