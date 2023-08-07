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

static SPI_HandleTypeDef &hspi = hspi3;

static Mcp356xController car(GpioOut(NMES_CAR_CS_GPIO_Port, NMES_CAR_CS_Pin, true), hspi, Mcp356xVersion::MCP3561);
static Mcp356xController acu(GpioOut(NMES_ACU_CS_GPIO_Port, NMES_ACU_CS_Pin, true), hspi, Mcp356xVersion::MCP3561);
static Mcp356xController isens(GpioOut(NMES_ISENS_CS_GPIO_Port, NMES_ISENS_CS_Pin, true), hspi, Mcp356xVersion::MCP3562);

static std::array < Mcp356xController*, 3 > mcps { &car, &acu, &isens };

static Mcp356x::ConfigGroup std_config =
{
	.adc_mode = Mcp356x::AdcMode::StandBy,
	.bias_current = Mcp356x::BiasCurrent::_0uA,
	.clk_sel = Mcp356x::ClockSelect::InternalNoOutput,
	.shut_down = Mcp356x::ShutDown::Active,
	.oversampling_ratio = Mcp356x::OversamplingRatio::_1024,
	.aclk_prescaller_div = Mcp356x::AClkPrescallerDiv::_2,
	// AutoZeroMux will perform Chx - Chy & Chy - Chx (minimizes mes offset)
	.az_mux = Mcp356x::AutoZeroMux::Enabled,
	.gain = Mcp356x::Gain::_2,
	.boost = Mcp356x::Boost::_1,
	.en_gain_cal = false,
	.en_off_cal = false,
	.en_crc = false,
	.crc_format = Mcp356x::CrcFormat::_16bit,
	.data_format = Mcp356x::DataFormat::_24bit_right_sgn,
	.conv_mode = Mcp356x::ConvMode::OneShotStandby,
	.en_stop = true,
	.en_fastcmd = true,
	// IrqPinState must be HighState
	.irq_pin_state = Mcp356x::IrqPinState::HighState,
	.irq_mdat_selection = Mcp356x::IrqMdatSelection::All,
};

static GpioIn charger_conected { CHARGER_DETECT_GPIO_Port, CHARGER_DETECT_Pin };
static GpioIn safety_detect { SAFETY_DETECT_GPIO_Port, SAFETY_DETECT_Pin };
static GpioIn air_pre_detect { AIR_PRE_DETECT_GPIO_Port, AIR_PRE_DETECT_Pin };
static GpioIn air_p_detect { AIR_P_DETECT_GPIO_Port, AIR_P_DETECT_Pin };
static GpioIn air_m_detect { AIR_M_DETECT_GPIO_Port, AIR_M_DETECT_Pin };

static double car_volt;
static double acu_volt;
static double isens_curr;

void vExternalMeasurmentsManagerTask(void *argument)
{
	bool carAdcCalib = true;
	bool acuAdcCalib = true;
	bool isensAdcCalib = true;

	constexpr auto setCar = 	[]{ car.setChannels(Mcp356x::MuxIn::Ch1, Mcp356x::MuxIn::Ch0); car.restartAdc(); };
	constexpr auto setAcu = 	[]{ acu.setChannels(Mcp356x::MuxIn::Ch1, Mcp356x::MuxIn::Ch0); acu.restartAdc(); };
	constexpr auto setIsens = 	[]{ isens.setChannels(Mcp356x::MuxIn::Ch3, Mcp356x::MuxIn::Ch2); isens.restartAdc(); };

	constexpr auto setCarCalib = 	[]{ car.setChannels(Mcp356x::MuxIn::Vcm, Mcp356x::MuxIn::Agnd); car.restartAdc(); };
	constexpr auto setAcuCalib = 	[]{ acu.setChannels(Mcp356x::MuxIn::Vcm, Mcp356x::MuxIn::Agnd); acu.restartAdc(); };
	constexpr auto setIsensCalib = 	[]{ isens.setChannels(Mcp356x::MuxIn::Vcm, Mcp356x::MuxIn::Agnd); isens.restartAdc(); };

	for(auto& mcp : mcps)
		mcp->configure(std_config);

	setCar();
	setAcu();
	setIsens();

	while(true)
	{
		FullStackDataInstance::set().ltc_data.charger_connected = charger_conected.isActive();
		FullStackDataInstance::set().external_data.safety_state = safety_detect.isActive();
		FullStackDataInstance::set().air.m_state = air_m_detect.isActive();
		FullStackDataInstance::set().air.p_state = air_p_detect.isActive();
		FullStackDataInstance::set().air.pre_state = air_pre_detect.isActive();

		if(car.dataReady())
		{
			auto org_car_volt = car.readVoltage();
			if(not carAdcCalib) //normal
			{
				setCarCalib();
				FullStackDataInstance::set().external_data.car_volt = org_car_volt * ExternalConfig::ADC_VOLT_COEF;
				car_volt = org_car_volt;
			}
			else //calibration
			{
				setCar();
				FullStackDataInstance::set().external_data.car_volt_calib = org_car_volt;
				double ratio = org_car_volt / 1.2;
				ratio = std::clamp(ratio, 0.25, 4.0);
				car.gain *= ratio;
			}
			carAdcCalib = !carAdcCalib;
		}
		if(acu.dataReady())
		{
			auto org_acu_volt = acu.readVoltage();
			if(not acuAdcCalib) //normal
			{
				setAcuCalib();
				FullStackDataInstance::set().external_data.acu_volt = org_acu_volt * ExternalConfig::ADC_VOLT_COEF;
				acu_volt = org_acu_volt;
			}
			else //calibration
			{
				setAcu();
				FullStackDataInstance::set().external_data.acu_volt_calib = org_acu_volt;
				double ratio = org_acu_volt / 1.2;
				ratio = std::clamp(ratio, 0.25, 4.0);
				acu.gain *= ratio;
			}
			acuAdcCalib = !acuAdcCalib;
		}
		if(isens.dataReady())
		{
			auto org_acu_curr = isens.readVoltage();
			if(not isensAdcCalib) //normal
			{
				setIsensCalib();
				FullStackDataInstance::set().external_data.acu_curr = org_acu_curr * ExternalConfig::ADC_CURR_COEF;
				isens_curr = org_acu_curr;
			}
			else //calibration
			{
				setIsens();
				FullStackDataInstance::set().external_data.acu_curr_calib = org_acu_curr;
				double ratio = org_acu_curr / 1.2;
				ratio = std::clamp(ratio, 0.25, 4.0);
				isens.gain *= ratio;
			}
			isensAdcCalib = !isensAdcCalib;
		}

		osDelay(100);
	}
}


