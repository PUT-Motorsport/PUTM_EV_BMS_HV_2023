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

	// all registers are shifted out in reverse order - byte2 byte1 byte0 instead of 0, 1, 3
	struct AdcVariantAlignRight : IAdcVariant, IReadRegister
	{
		uint8_t bytes[4];
	};
	struct AdcVariantAlignLeft : IAdcVariant, IReadRegister
	{
		private:
			uint8_t ignore;
		public:
			uint8_t bytes[3];
	};
	struct AdcVariantAlignRightSgn : IAdcVariant, IReadRegister
	{
		uint8_t sgn;
		uint8_t bytes[3];
	};
	struct AdcVariantAlignRightSgnId : IAdcVariant, IReadRegister
	{
		uint8_t id : 4;
		uint8_t sgn : 4;
		uint8_t bytes[3];
	};

	struct StatusByte : IReadRegister
	{
		public:
			uint8_t por_status : 1;
			uint8_t crccfg_status : 1;
			uint8_t dr_status : 1;
			uint8_t ndev_addr0 : 1;
			uint8_t dev_addr0 : 1;
			uint8_t dev_addr1 : 1;
		private:
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
		AdcMode adc_mode : 2 { 0 };
		BiasCurrent bias_current : 2 { 0 };
		ClockSelect clk_sel : 2 { 0 };
		ShutDown shut_down : 2 { 0 };
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
		private:
			uint8_t reserved_set_to_00 : 2 { 0b00 };
		public:
			Config1(OversamplingRatio ovr, AClkPrescallerDiv acpd) : oversampling_ratio(ovr), aclk_prescaller_div(acpd) { }
			Config1() = default;
			OversamplingRatio oversampling_ratio : 4 { 0 };
			AClkPrescallerDiv aclk_prescaller_div : 2 { 0 };
	};
	enum struct AutoZeroMux : uint8_t
	{
		Disabled,
		Enabled
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
		private:
			uint8_t reserved_set_to_11 : 2 { 0b11 };
		public:
			Config2(AutoZeroMux am, Gain g, Boost b) : az_mux(am), gain(g), boost(b) { }
			Config2() = default;
			AutoZeroMux az_mux : 1 { 0 };
			Gain gain : 3 { 0 };
			Boost boost : 2 { 0 };
	};
	enum struct CrcFormat : uint8_t
	{
		_16bit,
		_32bit
	};
	enum struct DataFormat : uint8_t
	{
		_24bit,
		_24bit_left,
		_24bit_right_sgn,
		_24bit_right_sgn_id
	};
	enum struct ConvMode : uint8_t
	{
		OneShotShudown = 0b01,
		OneShotStandby,
		Continuous
	};
	struct Config3 : IWriteReadRegister
	{
		bool en_gain_cal : 1 { 0 };
		bool en_off_cal : 1 { 0 };
		bool en_crc : 1 { 0 };
		CrcFormat crc_format : 1 { 0 };
		DataFormat data_format : 2 { 0 };
		ConvMode conv_mode : 2 { 0 };
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
	struct __packed Irq : IWriteReadRegister
	{
		public:
			Irq(bool _1, bool _2, IrqPinState _3, IrqMdatSelection _4) :
				en_stop{ _1 }, en_fastcmd{ _2 }, irq_pin_state{ _3 }, irq_mdat_selection{ _4 }
				{ }
			Irq() = default;
			bool en_stop : 1 { 0 };
			bool en_fastcmd : 1 { 0 };
			IrqPinState irq_pin_state: 1 { 0 };
			IrqMdatSelection irq_mdat_selection : 1 { 0 };
			const uint8_t por_status : 1 { 0 };
			const uint8_t crcconf_status : 1 { 0 };
			const uint8_t dr_status : 1 { 0 };
		private:
			uint8_t undefined : 1 { 0 };
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
		public:
			uint32_t chanel_selection : 16 { 0 };
		private:
			uint32_t undefined : 4 { 0 };
			uint32_t reserved_set_to_0 : 1 { 0b0 };
		public:
			DelayMul delay : 3 { 0 };
	};
	struct __packed Timer : IWriteReadRegister
	{
		uint8_t value[3];
	};
	struct __packed Offset : IWriteReadRegister
	{
		uint8_t value[3];
	};
	struct __packed GainCal : IWriteReadRegister
	{
		uint8_t value[3];
	};

struct ConfigGroup : public IWriteReadRegister
{
	public:
		ConfigGroup(AdcMode _1, BiasCurrent _2, ClockSelect _3, ShutDown _4, OversamplingRatio _5,
					AClkPrescallerDiv _6, AutoZeroMux _7, Gain _8, Boost _9, bool _10, bool _11,
					bool _12, CrcFormat _13, DataFormat _14, ConvMode _15, bool _16, bool _17,
					IrqPinState _18, IrqMdatSelection _19) :
					adc_mode{ _1 }, bias_current{ _2 }, clk_sel{ _3}, shut_down{ _4 },
					reserved_set_to_00{ 0b00 }, oversampling_ratio{ _5 }, aclk_prescaller_div{ _6 },
					reserved_set_to_11{ 0b11 }, az_mux{ _7 }, gain{ _8 }, boost{ _9 },
					en_gain_cal{ _10 }, en_off_cal{ _11 }, en_crc{ _12 }, crc_format{ _13 },
					data_format{ _14 }, conv_mode{ _15 },
					en_stop{ _16 }, en_fastcmd{ _17 }, irq_pin_state{ _18 }, irq_mdat_selection{ _19 }
					{ }
		ConfigGroup() = default;
		AdcMode adc_mode : 2 { 0 };
		BiasCurrent bias_current : 2 { 0 };
		ClockSelect clk_sel : 2 { 0 };
		ShutDown shut_down : 2 { 0 };
	private:
		uint8_t reserved_set_to_00 : 2 { 0b00 };
	public:
		OversamplingRatio oversampling_ratio : 4 { 0 };
		AClkPrescallerDiv aclk_prescaller_div : 2 { 0 };
	private:
		uint8_t reserved_set_to_11 : 2 { 0b11 };
	public:
		AutoZeroMux az_mux : 1 { 0 };
		Gain gain : 3 { 0 };
		Boost boost : 2 { 0 };
		bool en_gain_cal : 1 { 0 };
		bool en_off_cal : 1 { 0 };
		bool en_crc : 1 { 0 };
		CrcFormat crc_format : 1 { 0 };
		DataFormat data_format : 2 { 0 };
		ConvMode conv_mode : 2 { 0 };
	public:
		bool en_stop : 1 { 0 };
		bool en_fastcmd : 1 { 0 };
		IrqPinState irq_pin_state: 1 { 0 };
		IrqMdatSelection irq_mdat_selection : 1 { 0 };
		const uint8_t por_status : 1 { 0 };
		const uint8_t crcconf_status : 1 { 0 };
		const uint8_t dr_status : 1 { 0 };
	private:
		uint8_t undefined : 1 { 0 };
};

	template < typename Register >
	concept WriteReadRegister = std::is_base_of< IWriteReadRegister, Register >::value	and
								not std::is_polymorphic< Register >::value;

	template < typename Register >
	concept ReadRegister = 	std::is_base_of< IReadRegister, Register >::value		or
							std::is_base_of< IWriteReadRegister, Register >::value 	and
							not std::is_polymorphic< Register >::value;

	template < typename Variant >
	concept AdcVariant = 	std::is_base_of< IAdcVariant, Variant >::value 	and
							not std::is_polymorphic< Variant >::value 		and
							sizeof(Variant) == 4;

	template < WriteReadRegister Register >
	void serializeRegister(uint8_t *destination, Register const &source)
	{
		std::memcpy(destination, &source, sizeof(Register));
	}

	template < ReadRegister Register >
	void deserializeRegister(Register &destination, uint8_t const *source)
	{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wclass-memaccess"
		std::memcpy(&destination, source, sizeof(Register));
#pragma GCC diagnostic pop
	}
}

#endif /* INC_PERYPHERIALMANAGERS_MCP356XREGS_HPP_ */
