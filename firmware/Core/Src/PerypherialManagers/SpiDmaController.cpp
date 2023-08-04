/*
 * SpiDmaManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <PerypherialManagers/SpiDmaController.hpp>

static constexpr uint32_t bit31 = (1 << 31);

void SpiDmaController::initSpiDmaManager()
{
	xTxRxQueue1 = xQueueCreateStatic( queueSize, txRxStructSize, ucTxRxQueue1StorageArea, &xStaticTxRxQueue1 );
	xTxRxQueue2 = xQueueCreateStatic( queueSize, txRxStructSize, ucTxRxQueue2StorageArea, &xStaticTxRxQueue2 );
	xTxRxQueue3 = xQueueCreateStatic( queueSize, txRxStructSize, ucTxRxQueue3StorageArea, &xStaticTxRxQueue3 );
}

void SpiDmaController::spiRequestAndWait(SpiRequest &request)
{
	addRequest(request.handle);
	waitForNotify();
}

QueueHandle_t SpiDmaController::assignQueue(SPI_HandleTypeDef * hspi)
{
	if(hspi == &hspi1) return xTxRxQueue1;
	if(hspi == &hspi2) return xTxRxQueue2;
	if(hspi == &hspi3) return xTxRxQueue3;

	return nullptr;
}

void SpiDmaController::addRequest(SpiDmaHandle &rSpiDmaHandle)
{
	QueueHandle_t queueHandle = assignQueue(rSpiDmaHandle.hspi);
	if(queueHandle == nullptr); //Error

	xQueueSendToBack(queueHandle, &rSpiDmaHandle, portMAX_DELAY);
	if(uxQueueMessagesWaiting(queueHandle) == 1)
	{
		if(rSpiDmaHandle.cs != nullptr) rSpiDmaHandle.cs->activate();
		if(rSpiDmaHandle.pTxData != nullptr && rSpiDmaHandle.pRxData == nullptr)
			HAL_SPI_Transmit_DMA(rSpiDmaHandle.hspi, rSpiDmaHandle.pTxData, rSpiDmaHandle.dataSize);
		else if(rSpiDmaHandle.pRxData != nullptr && rSpiDmaHandle.pTxData == nullptr)
			HAL_SPI_Receive_DMA(rSpiDmaHandle.hspi, rSpiDmaHandle.pRxData, rSpiDmaHandle.dataSize);
		else
			HAL_SPI_TransmitReceive_DMA(rSpiDmaHandle.hspi, rSpiDmaHandle.pTxData, rSpiDmaHandle.pRxData, rSpiDmaHandle.dataSize);
	}
}

void SpiDmaController::waitForNotify()
{
	uint32_t pulNotificationValue = 0;
	while(true)
	{
		xTaskNotifyWait(0, bit31, &pulNotificationValue, portMAX_DELAY);
		if (pulNotificationValue & bit31) break;
	}
}

void HAL_SPI_Handle(SPI_HandleTypeDef * hspi)
{
	SpiDmaController::SpiDmaHandle spiDmaHandle = { 0 };
	QueueHandle_t queueHandle = SpiDmaController::assignQueue(hspi);
	//TODO: ???
	if(queueHandle == nullptr); //Error
	if(xQueueIsQueueEmptyFromISR(queueHandle) == pdTRUE); //Error

	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	bool yield = false;

	xQueueReceiveFromISR(queueHandle, &spiDmaHandle, &pxHigherPriorityTaskWoken);
	yield = yield || pxHigherPriorityTaskWoken;

	if(spiDmaHandle.cs != nullptr) spiDmaHandle.cs->deactivate();

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

SpiDmaController::StaticInitializer::StaticInitializer()
{
	SpiDmaController::initSpiDmaManager();
}

SpiRequest::SpiRequest(TaskHandle_t taskToNotify, GpioOut const *cs, SPI_HandleTypeDef const *hspi, uint8_t *pTxData, uint8_t *pRxData, size_t dataSize) :
handle(taskToNotify, (GpioOut*)cs, (SPI_HandleTypeDef*)hspi, pTxData, pRxData, dataSize) { }

SpiTxRequest::SpiTxRequest(SPI_HandleTypeDef const &hspi, uint8_t *tx_begin, size_t size) :
SpiRequest(xTaskGetCurrentTaskHandle(), nullptr, &hspi, tx_begin, nullptr, size) { }
SpiTxRequest::SpiTxRequest(GpioOut const &cs, SPI_HandleTypeDef const &hspi, uint8_t *tx_begin, size_t size) :
SpiRequest(xTaskGetCurrentTaskHandle(), &cs, &hspi, tx_begin, nullptr, size) { }

SpiRxRequest::SpiRxRequest(SPI_HandleTypeDef const &hspi, uint8_t *rx_begin, size_t size) :
SpiRequest(xTaskGetCurrentTaskHandle(), nullptr, &hspi, nullptr, rx_begin, size) { }
SpiRxRequest::SpiRxRequest(GpioOut const &cs, SPI_HandleTypeDef const &hspi, uint8_t *rx_begin, size_t size) :
SpiRequest(xTaskGetCurrentTaskHandle(), &cs, &hspi, nullptr, rx_begin, size) { }

SpiTxRxRequest::SpiTxRxRequest(SPI_HandleTypeDef const &hspi, uint8_t *tx_begin, uint8_t *rx_begin, size_t size) :
SpiRequest(xTaskGetCurrentTaskHandle(), nullptr, &hspi, tx_begin, rx_begin, size) { }
SpiTxRxRequest::SpiTxRxRequest(GpioOut const &cs, SPI_HandleTypeDef const &hspi, uint8_t *tx_begin, uint8_t *rx_begin, size_t size) :
SpiRequest(xTaskGetCurrentTaskHandle(), &cs, &hspi, tx_begin, rx_begin, size) { }
