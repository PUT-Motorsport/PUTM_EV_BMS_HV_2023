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

#include <app_freertos.h>
#include <PerypherialManagers/Mcp356xController.hpp>
#include <StackData.hpp>

//using AdcVar = MCP356x::AdcVariantAlignRightSgn;

enum struct State
{
	Init,
	Measure,
	Calibrate1,
	Calibrate2
} static state { State::Init };

#ifdef DEBUG
static float car_volt;
static float acu_volt;
static float isens_volt;
#endif

static SPI_HandleTypeDef &hspi = hspi3;

static Mcp356xController car(GpioOut(NMES_CAR_CS_GPIO_Port, NMES_CAR_CS_Pin, true), hspi, Mcp356xVersion::MCP3561);
static Mcp356xController acu(GpioOut(NMES_ACU_CS_GPIO_Port, NMES_ACU_CS_Pin, true), hspi, Mcp356xVersion::MCP3561);
static Mcp356xController isens(GpioOut(NMES_ISENS_CS_GPIO_Port, NMES_ISENS_CS_Pin, true), hspi, Mcp356xVersion::MCP3562);

static State car_state;
static State acu_state;
static State isens_state;

static Mcp356x::ConfigGroup std_config = []()
{
	Mcp356x::ConfigGroup c;
	c.adc_mode = Mcp356x::AdcMode::StandBy;
	c.bias_current = Mcp356x::BiasCurrent::_0uA;
	c.clk_sel = Mcp356x::ClockSelect::InternalNoOutput;
	c.shut_down = Mcp356x::ShutDown::Active;
	c.oversampling_ratio = Mcp356x::OversamplingRatio::_4096;
	c.aclk_prescaller_div = Mcp356x::AClkPrescallerDiv::_2;
	// AutoZeroMux will perform Chx - Chy & Chy - Chx (minimizes mes offset)
	c.az_mux = Mcp356x::AutoZeroMux::Enabled;
	c.gain = Mcp356x::Gain::_2;
	c.boost = Mcp356x::Boost::_1;
	c.en_gain_cal = false;
	c.en_off_cal = false;
	c.en_crc = false;
	c.crc_format = Mcp356x::CrcFormat::_16bit;
	c.data_format = Mcp356x::DataFormat::_24bit_right_sgn;
	c.conv_mode = Mcp356x::ConvMode::OneShotStandby;
	c.en_stop = true;
	c.en_fastcmd = true;
	// IrqPinState must be HighState
	c.irq_pin_state = Mcp356x::IrqPinState::HighState;
	c.irq_mdat_selection = Mcp356x::IrqMdatSelection::All;
	return c;
}();

static GpioIn charger_conected { CHARGER_DETECT_GPIO_Port, CHARGER_DETECT_Pin };
static GpioIn safety_detect { SAFETY_DETECT_GPIO_Port, SAFETY_DETECT_Pin };
static GpioIn air_pre_detect { AIR_PRE_DETECT_GPIO_Port, AIR_PRE_DETECT_Pin };
static GpioIn air_p_detect { AIR_P_DETECT_GPIO_Port, AIR_P_DETECT_Pin };
static GpioIn air_m_detect { AIR_M_DETECT_GPIO_Port, AIR_M_DETECT_Pin };

constexpr auto set = [](Mcp356xController & dev, Mcp356x::MuxIn ch_p, Mcp356x::MuxIn ch_n)
{
	dev.setChannels(ch_p, ch_n);
	dev.restartAdc();
};

static void init(Mcp356xController& dev, State &state, Mcp356x::MuxIn ch_p, Mcp356x::MuxIn ch_m)
{
	state = State::Measure;
	dev.configure(std_config);
	set(dev, ch_p, ch_m);
}

static  void measure(Mcp356xController& dev, State &state, std::atomic<float> &mes)
{
	if(dev.dataReady())
	{
		state = State::Calibrate1;
		auto org_volt = dev.readVoltage();
		set(dev, Mcp356x::MuxIn::Vcm, Mcp356x::MuxIn::Agnd);
		mes = org_volt;
#ifdef DEBUG
		if(&dev == &car) car_volt = org_volt;
		else if(&dev == &acu) acu_volt = org_volt;
		else if(&dev == &isens) isens_volt = org_volt;
#endif
	}
}

static void calibration1(Mcp356xController& dev, State &state)
{
	if(dev.dataReady())
	{
		state = State::Calibrate2;
		dev.gain *= std::clamp(dev.readVoltage() / 1.2, 0.25, 4.0);
		set(dev, Mcp356x::MuxIn::RefInM, Mcp356x::MuxIn::Agnd);
	}
}

static void calibration2(Mcp356xController& dev, State &state, Mcp356x::MuxIn ch_p, Mcp356x::MuxIn ch_m)
{
//	if(dev.dataReady())
//	{
		state = State::Measure;
//		dev.offset = 0.0 - dev.readVoltage();
		set(dev, ch_p, ch_m);
//	}
}

void vExternalMeasurmentsManagerTask(void *argument)
{
	while(true)
	{
		FullStackDataInstance::set().ltc_data.charger_connected = not charger_conected.isActive();
		FullStackDataInstance::set().external_data.safety_state = safety_detect.isActive();

		FullStackDataInstance::set().air_detect.m_state = air_m_detect.isActive();
		FullStackDataInstance::set().air_detect.p_state = air_p_detect.isActive();
		FullStackDataInstance::set().air_detect.pre_state = air_pre_detect.isActive();

		switch(car_state)
		{
			case State::Init:
				init(car, car_state, Mcp356x::MuxIn::Ch0, Mcp356x::MuxIn::Ch1);
				break;
			case State::Measure:{
				// FIXME
				std::atomic<float> raw_data{};
				measure(car, car_state, raw_data);
				float voltage = -1.0f * (raw_data +0.000221111884f) * 50.411f / 0.114356004f;
				FullStackDataInstance::set().external_data.car_volt = voltage;
				break;
			}
			case State::Calibrate1:
				calibration1(car, car_state);
				break;
			case State::Calibrate2:
				calibration2(car, car_state, Mcp356x::MuxIn::Ch0, Mcp356x::MuxIn::Ch1);
		}
		switch(acu_state)
		{
			case State::Init:
				init(acu, acu_state, Mcp356x::MuxIn::Ch0, Mcp356x::MuxIn::Ch1);
				break;
			case State::Measure: {
				std::atomic<float> raw_data{};
				measure(acu, acu_state, raw_data);
				float voltage = -1.0f * (raw_data -0.000586072507f) * 60.41f / 0.147790566f;
				FullStackDataInstance::set().external_data.acu_volt = voltage;
				break;
			}
			case State::Calibrate1:
				calibration1(acu, acu_state);
				break;
			case State::Calibrate2:
				calibration2(acu, acu_state, Mcp356x::MuxIn::Ch0, Mcp356x::MuxIn::Ch1);
		}
		switch(isens_state)
		{
			case State::Init:
				init(isens, isens_state, Mcp356x::MuxIn::Ch2, Mcp356x::MuxIn::Ch3);
				break;
			case State::Measure:{
				// FIXME
				std::atomic<float> raw_data{};
				measure(isens, isens_state, raw_data);
				float current = ((raw_data - 0.0235465225f) * 10.0f / 0.061959736f + 0.45f) * -1.0f;
				FullStackDataInstance::set().external_data.acu_curr = current;
				break;
			}
			case State::Calibrate1:
				calibration1(isens, isens_state);
				break;
			case State::Calibrate2:
				calibration2(isens, isens_state, Mcp356x::MuxIn::Ch2, Mcp356x::MuxIn::Ch3);
		}
		osDelay(20);
	}
}


