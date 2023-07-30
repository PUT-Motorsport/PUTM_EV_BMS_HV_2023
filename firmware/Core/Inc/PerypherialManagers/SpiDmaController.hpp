/*
 * SpiDmaManager.hpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#ifndef INC_SPI_SPIDMAMANAGER_HPP_
#define INC_SPI_SPIDMAMANAGER_HPP_

#include "main.h"
#include "FreeRTOS.h"
#include "spi.h"
#include "task.h"
#include "queue.h"
#include "PerypherialManagers/Gpio.hpp"

class SpiRequest;

class SpiDmaController
{
	protected:
		struct SpiDmaHandle
		{
			TaskHandle_t taskToNotify;
			GpioOut *cs;
			SPI_HandleTypeDef *hspi;
			uint8_t *pTxData;
			uint8_t *pRxData;
			size_t dataSize;
		};

		static inline const size_t queueSize = 2;
		static inline const size_t txRxStructSize = sizeof(SpiDmaHandle);

		static inline QueueHandle_t xTxRxQueue1;
		static inline QueueHandle_t xTxRxQueue2;
		static inline QueueHandle_t xTxRxQueue3;
		static inline uint8_t ucTxRxQueue1StorageArea[ queueSize * txRxStructSize ];
		static inline uint8_t ucTxRxQueue2StorageArea[ queueSize * txRxStructSize ];
		static inline uint8_t ucTxRxQueue3StorageArea[ queueSize * txRxStructSize ];
		static inline StaticQueue_t xStaticTxRxQueue1;
		static inline StaticQueue_t xStaticTxRxQueue2;
		static inline StaticQueue_t xStaticTxRxQueue3;

		static void addRequest(SpiDmaHandle &rSpiDmaRxTxHandle);
		static void waitForNotify();
		static void initSpiDmaManager();

		static inline QueueHandle_t assignQueue(SPI_HandleTypeDef * hspi);

		class StaticInitializer
		{
			public:
				StaticInitializer();
		};
		static inline StaticInitializer initializer;

		//friend void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * hspi);
		//friend void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi);
		friend void HAL_SPI_Handle(SPI_HandleTypeDef * hspi);
		friend class SpiRequest;
	public:

		static void spiRequestAndWait(SpiRequest &request);
};

class SpiRequest
{
	public:
		SpiRequest(TaskHandle_t taskToNotify, GpioOut const *cs, SPI_HandleTypeDef const *hspi, uint8_t *pTxData, uint8_t *pRxData, size_t dataSize);
		virtual ~SpiRequest() = default;
		friend class SpiDmaController;
	protected:
		 SpiDmaController::SpiDmaHandle handle;
};

class SpiTxRequest : public SpiRequest
{
	public:
		SpiTxRequest(SPI_HandleTypeDef const &hspi, uint8_t *tx_begin, size_t size);
		SpiTxRequest(GpioOut const &cs, SPI_HandleTypeDef const &hspi, uint8_t *tx_begin, size_t size);
};

class SpiRxRequest : public SpiRequest
{
	public:
		SpiRxRequest(SPI_HandleTypeDef const &hspi, uint8_t *rx_begin, size_t size);
		SpiRxRequest(GpioOut const &cs, SPI_HandleTypeDef const &hspi, uint8_t *rx_begin, size_t size);
};

class SpiTxRxRequest : public SpiRequest
{
	public:
		SpiTxRxRequest(SPI_HandleTypeDef const &hspi, uint8_t *tx_begin, uint8_t *rx_begin, size_t size);
		SpiTxRxRequest(GpioOut const &cs, SPI_HandleTypeDef const &hspi, uint8_t *tx_begin, uint8_t *rx_begin, size_t size);
};

#endif /* INC_SPI_SPIDMAMANAGER_HPP_ */
