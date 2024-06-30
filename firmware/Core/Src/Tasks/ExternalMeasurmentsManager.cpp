/*
 * ExternalMeasurmentsManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <main.h>
#include <spi.h>
#include <numeric>
#include <algorithm>
#include <functional>
#include <optional>

#include <app_freertos.h>
#include <PerypherialManagers/Mcp356xController.hpp>
#include <StackData.hpp>

static SPI_HandleTypeDef &hspi = hspi3;

static Mcp356xController car(GpioOut(NMES_CAR_CS_GPIO_Port, NMES_CAR_CS_Pin, true), hspi);
static Mcp356xController acu(GpioOut(NMES_ACU_CS_GPIO_Port, NMES_ACU_CS_Pin, true), hspi);
static Mcp356xController isens(GpioOut(NMES_ISENS_CS_GPIO_Port, NMES_ISENS_CS_Pin, true), hspi);

// num of cyckles after which the adc mes will be restarted in case no new data was received
static constexpr uint32_t timeout = 4;

static constexpr Mcp356x::ConfigGroup std_config = []()
{
	Mcp356x::ConfigGroup c;
	c.adc_mode = Mcp356x::AdcMode::StandBy;
	c.bias_current = Mcp356x::BiasCurrent::_0uA;
	c.clk_sel = Mcp356x::ClockSelect::InternalNoOutput;
	c.shut_down = Mcp356x::ShutDown::Active;
	c.oversampling_ratio = Mcp356x::OversamplingRatio::_16384;
	c.aclk_prescaller_div = Mcp356x::AClkPrescallerDiv::_4;
	// AutoZeroMux will perform Chx - Chy & Chy - Chx (minimizes mes offset)
	c.az_mux = Mcp356x::AutoZeroMux::Enabled;
	c.gain = Mcp356x::Gain::_2;
	c.boost = Mcp356x::Boost::_2;
	c.en_gain_cal = false;
	c.en_off_cal = false;
	c.en_crc = false;
	c.crc_format = Mcp356x::CrcFormat::_16bit;
	c.data_format = Mcp356x::DataFormat::_24bit_right_sgn;
	c.conv_mode = Mcp356x::ConvMode::Continuous;
	c.en_stop = true;
	c.en_fastcmd = true;
	// IrqPinState must be HighState
	c.irq_pin_state = Mcp356x::IrqPinState::HighState;
	c.irq_mdat_selection = Mcp356x::IrqMdatSelection::All;
	return c;
}();

extern GpioIn charger_detect;
extern GpioIn safety_detect;


void vExternalMeasurmentsManagerTask(void *argument)
{
	car.init();
	acu.init();
	isens.init();

	car.configure(std_config);
	acu.configure(std_config);
	isens.configure(std_config);

	car.setChannels(Mcp356x::MuxIn::Ch0, Mcp356x::MuxIn::Ch1);
	acu.setChannels(Mcp356x::MuxIn::Ch0, Mcp356x::MuxIn::Ch1);
	isens.setChannels(Mcp356x::MuxIn::Ch0, Mcp356x::MuxIn::Agnd);

	car.restartAdc();
	acu.restartAdc();
	isens.restartAdc();

	while(true)
	{
		osDelay(20);

		FullStackDataInstance::set().ltc_data.charger_connected = charger_detect.isActive();
		FullStackDataInstance::set().external_data.safety_state = safety_detect.isActive();

//		FullStackDataInstance::set().air_detect.m_state = air_m_detect.isActive();
//		FullStackDataInstance::set().air_detect.p_state = air_p_detect.isActive();
//		FullStackDataInstance::set().air_detect.pre_state = air_pre_detect.isActive();

		if(car.dataReady())
		{
			FullStackDataInstance::set().external_data.car_volt = car.readVoltage();
			//car.restartAdc();
		}
		if(acu.dataReady())
		{
			FullStackDataInstance::set().external_data.acu_volt = acu.readVoltage();
			//acu.restartAdc();
		}
		if(isens.dataReady())
		{
			FullStackDataInstance::set().external_data.acu_curr = isens.readVoltage();
			//isens.restartAdc();
		}
	}
}


