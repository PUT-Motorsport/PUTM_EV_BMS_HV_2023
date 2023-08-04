/*
 * LTCManager.cpp
 *
 *  Created on: Jul 1, 2023
 *      Author: Piotr Lesicki
 */


#include <MainHeader.hpp>

static SPI_HandleTypeDef &hspi = hspi2;
static LTC6811Controller ltc_ctrl(GpioOut(NLTC2_CS_GPIO_Port, NLTC2_CS_Pin, true), hspi);

void vLTCManagerTask(void *argument)
{
	ltc_ctrl.configure();

	while(true)
	{
		//ltc_ctrl.readVoltages(volts);
		ltc_ctrl.readVoltages(FullStackDataInstance::getAndModify().ltc_data.voltages);
		ltc_ctrl.readGpioTemp(FullStackDataInstance::getAndModify().ltc_data.temp);

		if(FullStackDataInstance::get().ltc_data.charger_connected)
		{
			ltc_ctrl.setDischarge(FullStackDataInstance::get().ltc_data.discharge);
		}

		osDelay(100);
	}
}
