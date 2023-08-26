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
#include <PerypherialManagers/LtcTemperatureCalculation.hpp>
#include <ranges>
#include <algorithm>

static SPI_HandleTypeDef &hspi = hspi2;
static Ltc6811Controller ltc_ctrl(GpioOut(NLTC2_CS_GPIO_Port, NLTC2_CS_Pin, true), hspi);

enum struct States
{
	Init,
	Normal,
	Charging,
	OpticalVisualization
} static state { States::Init };

constexpr static std::array<float, LtcConfig::TEMP_COUNT> offsets = {-1.0153,-0.8715,0.0999,-2.1395,-1.7146,-1.8290,0.3097,-1.3584,-3.7277,-1.4793,1.4041,3.6908,2.5545,3.0929,1.2957,2.8936,0.5405,1.4321,-5.6945,1.2363,3.7853,-1.5610,4.0510,1.7748,-0.1558,1.9776,2.3797,-7.7253,0.6873,3.2048,0.6419,3.6699,1.8971,2.2328,0.3936,1.3936,-4.8421,-3.8094,-1.0708,0.2818,0.1104,-1.2865,-2.0414,-2.1918,-2.5186};

static inline void calc_temp(){
	for(size_t i = 0; i < LtcConfig::TEMP_COUNT; ++i){
		FullStackDataInstance::set().ltc_data.temp_C.at(i) = LtcCalculateTemperature((uint16_t)FullStackDataInstance::get().ltc_data.temp[i]) - offsets[i];
	}
	const auto& t_array = FullStackDataInstance::set().ltc_data.temp_C;
	float t_max = *std::ranges::max_element(t_array.begin(), t_array.end());
	FullStackDataInstance::set().ltc_data.max_temp = t_max;
	float t_min = *std::ranges::min_element(t_array.begin(), t_array.end());
	FullStackDataInstance::set().ltc_data.min_temp = t_min;
}

static inline void init()
{
	state = States::Normal;
	ltc_ctrl.configure();
}

static inline void normal()
{
	if(FullStackDataInstance::get().ltc_data.charger_connected)
		state = States::Charging;
	else if(FullStackDataInstance::get().usb_events.discharge_optical_visualisation)
		state = States::OpticalVisualization;

	ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
	ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);
	calc_temp();
}

static inline void charging()
{
	if(not FullStackDataInstance::get().ltc_data.charger_connected)
		state = States::Normal;

	ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
	ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);
	ltc_ctrl.setDischarge(FullStackDataInstance::get().ltc_data.discharge);
	calc_temp();
}

static inline void opticalVisualization()
{
	if(FullStackDataInstance::get().ltc_data.charger_connected)
		state = States::Charging;
	else if(not FullStackDataInstance::get().usb_events.discharge_optical_visualisation)
		state = States::Normal;
	ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
	ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);

	static size_t num = 0;

	for(size_t i = 0; i < LtcConfig::CHAIN_SIZE; i++)
	{
		for(size_t j = 0; j < 9; j ++)
		{
			size_t index = i * 9;
			if(num == j)
				FullStackDataInstance::set().ltc_data.discharge[index + j] = true;
			else
				FullStackDataInstance::set().ltc_data.discharge[index + j] = false;
		}
	}
	num++;
	if (num >= 9) num = 0;
	ltc_ctrl.setDischarge(FullStackDataInstance::get().ltc_data.discharge);
	calc_temp();
}

void vLTCManagerTask(void *argument)
{
	//init();
	while(true)
	{
		switch(state)
		{
			case States::Init:
				init();
				break;
			case States::Normal:
				normal();
				break;
			case States::Charging:
				charging();
				break;
			case States::OpticalVisualization:
				opticalVisualization();
				break;
			default:
				state = States::Normal;
				break;
		}

		osDelay(100);
	}
}
