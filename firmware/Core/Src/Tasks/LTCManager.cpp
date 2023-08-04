/*
 * LTCManager.cpp
 *
 *  Created on: Jul 1, 2023
 *      Author: Piotr Lesicki
 */

#include "PerypherialManagers/LtcController.hpp"
#include "app_freertos.h"
#include "main.h"
#include "PerypherialManagers/Gpio.hpp"
#include "StackData.hpp"

static SPI_HandleTypeDef &hspi = hspi2;
static LtcController ltc_ctrl(GpioOut(NLTC2_CS_GPIO_Port, NLTC2_CS_Pin, true), hspi);

//static std::array < std::array < float, 12 >, chain_size > volts;
//static std::array < std::array < bool, 12 >, chain_size > discharge;

void vLTCManagerTask(void *argument)
{
	ltc_ctrl.configure();
	//ltc_ctrl.setDischarge(discharge);

	while(true)
	{
		//ltc_ctrl.readVoltages(volts);
		ltc_ctrl.readVoltages(FullStackDataInstance::getAndModify().ltc_data.voltages);

		//if(full_stack_i.get().ltc_data.charger_connected)
		//{
			ltc_ctrl.setDischarge(FullStackDataInstance::get().ltc_data.discharge);
		//}

		osDelay(100);
	}
}
