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

template < typename T >
using RegArray 	= std::array < T, LtcConfig::CHAIN_SIZE >;
template < typename T >
using DataArray = std::array < T, LtcConfig::CHAIN_SIZE * 12 >;
template < typename T >
using GpioArray = std::array < T, LtcConfig::CHAIN_SIZE * 5 >;

using fsdi = FullStackDataInstance;

static SPI_HandleTypeDef &hspi = hspi2;
static Ltc6811Controller ltc_ctrl(GpioOut(NLTC2_CS_GPIO_Port, NLTC2_CS_Pin, true), hspi);

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

	static DataArray < float > voltages;
	ltc_ctrl.readVoltages(&voltages);
	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		size_t offset_cell = ltc * CELLS_PER_LTC;
		for(size_t cell = 0; cell < CELLS_PER_LTC; cell++)
		{
			size_t offset_ltc = ltc * 12;
			size_t maped_cell = CELL_TO_CH_MAP[cell];
			fsdi::set().ltc_data.voltages[cell + offset_cell] = voltages[maped_cell + offset_ltc];
		}
	}

	static GpioArray < float > gpio;
	ltc_ctrl.readGpio(&gpio);
	for(size_t ltc = 0; ltc < CHAIN_SIZE; ltc++)
	{
		size_t offset = ltc * TEMP_PER_LTC;
		for(size_t i = 0; i < TEMP_PER_LTC; i++)
		{
			fsdi::set().ltc_data.temp[i + offset] = gpio[i + offset];
		}
	}

//	ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
//	ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);
//	calcTemp();
}

static void charging()
{
	if(not FullStackDataInstance::get().ltc_data.charger_connected)
		state = States::Normal;

//	ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
//	ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);
//	ltc_ctrl.setDischarge(FullStackDataInstance::get().ltc_data.discharge);
//	calcTemp();
}

static void opticalVisualization()
{
//	if(FullStackDataInstance::get().ltc_data.charger_connected)
//		state = States::Charging;
//	else if(not FullStackDataInstance::get().usb_events.discharge_optical_visualisation)
//		state = States::Normal;
//	ltc_ctrl.readVoltages(FullStackDataInstance::set().ltc_data.voltages);
//	ltc_ctrl.readGpioTemp(FullStackDataInstance::set().ltc_data.temp);

	static size_t num = 0;
	static size_t delay = 0;

	static DataArray < bool > discharges { false };

	delay++;
	if (delay < 10) return;

	for(size_t ltc = 0; ltc < LtcConfig::CHAIN_SIZE; ltc++)
	{
		for(size_t cell = 0; cell < LtcConfig::CELLS_PER_LTC; cell++)
		{
			size_t offset = ltc * 12;
			size_t maped_cell = CELL_TO_CH_MAP[cell];
			if(num == cell)
				discharges[offset + maped_cell] = true;
			else
				discharges[offset + maped_cell] = false;
		}
	}

	delay = 0;
	num++;
	if (num >= LtcConfig::CELLS_PER_LTC) num = 0;

	ltc_ctrl.setDischarge(&discharges);
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
