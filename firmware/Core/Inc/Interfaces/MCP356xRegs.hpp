/*
 * MCP356xRegs.hpp
 *
 *  Created on: 2 sie 2023
 *      Author: piotr
 */

#ifndef INC_PERYPHERIALMANAGERS_MCP356XREGS_HPP_
#define INC_PERYPHERIALMANAGERS_MCP356XREGS_HPP_

#include <main.h>
#include <concepts>
#include <cstring>

namespace Mcp356x
{
	struct IWriteReadRegister { };
	struct IReadRegister { };
	struct IAdcVariant { };

	struct AdcVariantAlignRight : IAdcVariant, IReadRegister
	{
		uint32_t sgn : 1;
		uint32_t value : 23;
		uint32_t unused : 8;
	};
	struct AdcVariantAlignLeft : IAdcVariant, IReadRegister
	{
		uint32_t unused : 8;
		uint32_t sgn : 1;
		uint32_t value : 23;
	};
	struct AdcVariantAlignRightSgn : IAdcVariant, IReadRegister
	{
		uint32_t value : 24;
		uint32_t sgn : 8;
	} ;
	struct AdcVariantAlignRightSgnId : IAdcVariant, IReadRegister
	{
		uint32_t value : 24;
		uint32_t sgn : 4;
		uint32_t id : 4;
	};

	struct StatusByte : IReadRegister
	{
		uint8_t por_status : 1;
		uint8_t crccfg_status : 1;
		uint8_t dr_status : 1;
		uint8_t ndev_addr0 : 1;
		uint8_t dev_addr0 : 1;
		uint8_t dev_addr1 : 1;
		uint8_t ignore : 2;
	};

//	enum struct ChannelId : uint8_t
//	{
//		not_defined
//	};

	enum struct AdcMode : uint8_t
	{
		ShutDown = 		0b00,
		StandBy = 		0b10,
		Conversion = 	0b11
	};
	enum struct BiasCurrent : uint8_t
	{
		_0uA = 		0b00,
		_0_9uA = 	0b01,
		_3_7uA = 	0b10,
		_15uA =		0b11
	};
	enum struct ClockSelect : uint8_t
	{
		External = 			0b01,
		InternalNoOutput =	0b10,
		InternalOutput = 	0b11
	};
	enum struct ShutDown : uint8_t
	{
		Active = 	0b11,
		ShutDown =	0b00,
	};
	struct Config0 : IWriteReadRegister
	{
		AdcMode adc_mode : 2;
		BiasCurrent bias_current : 2;
		ClockSelect clk_sel : 2;
		ShutDown shut_down : 2;
	};
	enum struct OversamplingRatio : uint8_t
	{
		_32,
		_64,
		_128,
		_256,
		_512,
		_1024,
		_2048,
		_4096,
		_8192,
		_16384,
		_20480,
		_24576,
		_40960,
		_49152,
		_81920,
		_98304
	};
	enum struct AClkPrescallerDiv : uint8_t
	{
		_1,
		_2,
		_4,
		_8
	};
	struct Config1 : IWriteReadRegister
	{
		uint8_t reserved_set_to_00 : 2;
		OversamplingRatio oversampling_ratio : 4;
		AClkPrescallerDiv aclk_prescaller_div : 2;
	};
	enum struct AzMux : uint8_t
	{
		disabled,
		active
	};
	enum struct Gain : uint8_t
	{
		_0_33, // 1/3
		_1,
		_2,
		_4,
		_8,
		_16,
		_32,
		_64
	};
	enum struct Boost : uint8_t
	{
		_0_5,
		_0_66,
		_1,
		_2
	};
	struct Config2 : IWriteReadRegister
	{
		uint8_t reserved_set_to_11 : 2;
		AzMux az_mux : 1;
		Gain gain : 3;
		Boost boost : 2;
	};
	enum struct CrcFormat : uint8_t
	{
		_16bit,
		_32bit
	};
	enum struct DataFormat : uint8_t
	{
		_24bit,
		_32bit_left,
		_32bit_right_sgn,
		_32bit_right_sgn_id
	};
	enum struct ConvMode : uint8_t
	{
		OneShotShudown = 0b01,
		OneShotStandby,
		Continuous
	};
	struct Config3 : IWriteReadRegister
	{
		uint8_t en_gain_cal : 1;
		uint8_t en_off_cal : 1;
		uint8_t en_crc : 1;
		CrcFormat crc_format : 1;
		DataFormat data_format : 2;
		ConvMode conv_mode : 2;
	};
	enum struct IrqPinState : uint8_t
	{
		HighZ,
		HighState
	};
	enum struct IrqMdatSelection : uint8_t
	{
		All,
		PorAndCrcOnly
	};
	struct IRQ : IWriteReadRegister
	{
		uint8_t en_stop : 1;
		uint8_t en_fastcmd : 1;
		IrqPinState irq_pin_state: 1;
		IrqMdatSelection irq_mdat_selection : 1;
		uint8_t por_status : 1;
		uint8_t crcconf_status : 1;
		uint8_t dr_status : 1;
		uint8_t undefined : 1;
	};
	enum struct MuxIn : uint8_t
	{
		Ch0 = 		0b0000,
		Ch1 = 		0b0001,
		Ch2 = 		0b0010,
		Ch3 = 		0b0011,
		Ch4 = 		0b0100,
		Ch5 = 		0b0101,
		Ch6 = 		0b0110,
		Ch7 = 		0b0111,
		Agnd = 		0b1000,
		Avdd = 		0b1001,
		RefInM = 	0b1011,
		RefInP =	0b1100,
		TempDP =	0b1101,
		TempDM = 	0b1110,
		Vcm =		0b1111
	};
	struct Mux : IWriteReadRegister
	{
		MuxIn in_m : 4;
		MuxIn in_p : 4;
	};
	enum struct DelayMul : uint8_t
	{
		_0,
		_8,
		_16,
		_32,
		_64,
		_128,
		_256,
		_512
	};
	struct Scan : IWriteReadRegister
	{
		uint32_t chanel_selection : 16;
		uint32_t undefined : 4;
		uint32_t reserved_set_to_0 : 1;
		DelayMul delay : 3;
	};
	struct Timer : IWriteReadRegister
	{
		uint32_t value : 24;
	};
	struct Offset : IWriteReadRegister
	{
		uint32_t value : 24;
	};
	struct GainCal : IWriteReadRegister
	{
		uint32_t value : 24;
	};
	//there are other reserved / unused

	// config groped into one larger register (sizeof = 4)
	// for write optimization
	struct ConfigGroup : IWriteReadRegister
	{
		Config0 config0;
		Config1 config1;
		Config2 config2;
		Config3 config3;
	};

	template < typename Register >
	concept WriteReadRegister = std::is_base_of< IWriteReadRegister, Register >::value 	and
								std::is_standard_layout< Register >::value				and
								std::is_trivial< Register >::value;

	template < typename Register >
	concept ReadRegister = 	std::is_base_of< IReadRegister, Register >::value 	and
							std::is_standard_layout< Register >::value			and
							std::is_trivial< Register >::value;

	template < typename Variant >
	concept AdcVariant = 	std::is_base_of< IAdcVariant, Variant >::value 	and
							sizeof(Variant) == 4							and
							std::is_standard_layout< Variant >::value		and
							std::is_trivial< Variant >::value;

	template < WriteReadRegister Register >
	void serializeRegister(uint8_t *destination, Register const &source)
	{
		std::memcpy(destination, &source, sizeof(Register));
	}

	template < ReadRegister Register >
	void deserializeRegister(Register &destination, uint8_t const *source)
	{
		std::memcpy(&destination, source, sizeof(Register));
	}
}

#endif /* INC_PERYPHERIALMANAGERS_MCP356XREGS_HPP_ */
