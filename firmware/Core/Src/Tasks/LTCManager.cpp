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

using namespace LtcConfig;

static SPI_HandleTypeDef &hspi = hspi2;
static Ltc6811Controller ltc_ctrl(GpioOut(NLTC2_CS_GPIO_Port, NLTC2_CS_Pin, true), hspi);
using fsdi = FullStackDataInstance;

enum struct States
{
	Init,
	Normal,
	Charging,
	OpticalVisualization
} static state { States::Init };

constexpr static std::array<float, LtcConfig::TEMP_COUNT> offsets { 0 };// = { 2.7623, 2.7562, 2.8488,2.5648,2.3735,2.5216,3.1420,2.5833,2.0216,2.8241,3.1296,3.6019,3.4630,3.4846,2.9691,3.5679,2.9136,3.2685,-2.9940,3.0586,3.6605,-2.9910,3.6883,3.5247,-0.6958,3.3951,3.4414,-3.1295,3.0340,3.6759,0.1325,3.8735,3.4660,3.4846,3.1111,3.1019,1.9599,1.9691,2.4969,2.8858,2.6173,2.3920,2.5185,2.2870,2.2099 };

static void calcTemp()
{
	for(size_t i = 0; i < LtcConfig::TEMP_COUNT; ++i)
	{
		fsdi::set().ltc_data.temp_C.at(i) = LtcCalculateTemperature((uint16_t)fsdi::get().ltc_data.temp[i]) - offsets.at(i);
	}
	const auto& t_array = fsdi::set().ltc_data.temp_C;
	float t_max = *std::ranges::max_element(t_array.begin(), t_array.end());
	fsdi::set().ltc_data.max_temp = t_max;
	float t_min = *std::ranges::min_element(t_array.begin(), t_array.end());
	fsdi::set().ltc_data.min_temp = t_min;
}

static void init()
{
	ltc_ctrl.configure();
	state = States::Normal;
}

static void normal()
{
	if(fsdi::get().ltc_data.charger_connected)
		state = States::Charging;
	else if(fsdi::get().usb_events.discharge_optical_visualisation)
		state = States::OpticalVisualization;

	auto voltages = ltc_ctrl.readVoltages();
	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		size_t offset_cell = ltc * CELLS_PER_LTC;
		for(size_t cell = 0; cell < CELLS_PER_LTC; cell++)
		{
			size_t offset_ltc = ltc * 12;
			size_t maped_cell = CELL_TO_CH_MAP[cell];
			auto& volt = voltages[maped_cell + offset_ltc];
			if(std::holds_alternative<float>(volt))
			{
				fsdi::set().ltc_data.voltages[cell + offset_cell] = std::get<float>(volt);
			}
			else
			{
				fsdi::set().ltc_data.voltages[cell + offset_cell] = -1.f;
			}
		}
	}

	auto gpio = ltc_ctrl.readGpio();
	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		size_t offset = ltc * 5;
		for(size_t i = 0; i < 5; i++)
		{
			if(std::holds_alternative<float>(gpio[i + offset]))
			{
				fsdi::set().ltc_data.temp[i + offset] = std::get<float>(gpio[i + offset]);
			}
			else
			{
				fsdi::set().ltc_data.temp[i + offset] = -1.f;
			}
		}

	}

	//ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
	//ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);
	//calcTemp();
}

static void charging()
{
	if(not FullStackDataInstance::get().ltc_data.charger_connected)
		state = States::Normal;

	//ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
	//ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);
	//ltc_ctrl.setDischarge(FullStackDataInstance::get().ltc_data.discharge);
	//calcTemp();
}

static void opticalVisualization()
{
	if(FullStackDataInstance::get().ltc_data.charger_connected)
		state = States::Charging;
	else if(not FullStackDataInstance::get().usb_events.discharge_optical_visualisation)
		state = States::Normal;
	//ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
	//ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);

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
	//ltc_ctrl.setDischarge(FullStackDataInstance::get().ltc_data.discharge);
	//calcTemp();
}

void vLTCManagerTask(void *argument)
{
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
