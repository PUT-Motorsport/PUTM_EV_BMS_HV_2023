/*
 * LTCManager.cpp
 *
 *  Created on: Jul 1, 2023
 *      Author: Piotr Lesicki
 */


#include <main.h>
#include <spi.h>

#include <app_freertos.h>
#include <PerypherialManagers/Ltc6811Controller.hpp>
#include <StackData.hpp>

static SPI_HandleTypeDef &hspi = hspi2;
static Ltc6811Controller ltc_ctrl(GpioOut(NLTC2_CS_GPIO_Port, NLTC2_CS_Pin, true), hspi);

void vLTCManagerTask(void *argument)
{
	ltc_ctrl.configure();

	while(true)
	{
		//ltc_ctrl.readVoltages(volts);
		ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
		ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);

		if(FullStackDataInstance::get().ltc_data.charger_connected)
		{
			ltc_ctrl.setDischarge(FullStackDataInstance::get().ltc_data.discharge);
		}

		osDelay(100);
	}
}
