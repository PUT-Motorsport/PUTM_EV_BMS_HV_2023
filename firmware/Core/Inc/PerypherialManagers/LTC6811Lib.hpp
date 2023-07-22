/*
 * LTC6811_lib.hpp
 *
 *  Created on: 14 maj 2023
 *      Author: Piotr Lesicki
 */

#ifndef INC_PUTM_LTC_6811_LTC6804_LIB_LTC6811LIB_HPP_
#define INC_PUTM_LTC_6811_LTC6804_LIB_LTC6811LIB_HPP_

// cross compatibility with mixed uCs is kind of a pain in the ass
// so for now there is this:
#define LTC6804_COMPATIBLE_ONLY 1

#include <cstring>
#include <type_traits>
#include <math.h>

#include "main.h"

#include "etl/array.h"
#include "PerypherialManagers/LTC6811CmdCodes.hpp"

// dummy structs for clarification for other shit
struct WrRdRegisterGroup { };
struct RdRegisterGroup { };

template < typename RegisterGroup >
inline std::array < uint8_t, 6 > serializeRegisterGroup(const RegisterGroup &data)
{
	std::array < uint8_t, 6 > buff { 0 };
	std::memcpy(buff.data(), &data, 6);
	return buff;
}

template < typename RegisterGroup >
void serializeRegisterGroup(const RegisterGroup &data, uint8_t const *begin)//, uint8_t const *end)
{
	std::memcpy(begin, &data, 6);
}

template < typename RegisterGroup >
inline RegisterGroup deserializeRegisterGroup(const std::array < uint8_t, 6 > &data)
{
	RegisterGroup buff;
	std::memcpy(&buff, data.data(), 6);
	return buff;
}

template < typename RegisterGroup >
inline RegisterGroup deserializeRegisterGroup(uint8_t const *begin)//, uint8_t const *end) // FIXME: don't pretend to be ranged based ...
{
	RegisterGroup buff;
	std::memcpy(&buff, begin, 6);
	return buff;
}

struct LTC6811
{
	constexpr static float cell_v_conv_coef = 0.000'1f;
	constexpr static float tmp_conv_coef = 0.000'1f / 0.007'5f;

	// convert ADC to cell voltage returns in [V]
	static inline float CellVConv(uint16_t value)
	{
		return float(value) * cell_v_conv_coef;
	}

	// internal die temperature returns in [*C]
	static inline float IntTmpConv(uint16_t value)
	{
		return float(value) * tmp_conv_coef - 273.f;
	}

	enum struct DischargeTime : uint8_t
	{
		Disable = 0x0,
		_0_5min = 0x1,
		_1min	= 0x2,
		_2min	= 0x3,
		_3min	= 0x4,
		_4min 	= 0x5,
		_5min	= 0x6,
		_10min 	= 0x7,
		_15min	= 0x8,
		_20min	= 0x9,
		_30min 	= 0xa,
		_40min	= 0xb,
		_60min	= 0xc,
		_75min	= 0xd,
		_90min	= 0xe,
		_120min	= 0xf
	};

	enum struct Gpio
	{
		_0,
		_1,
		_2,
		_3,
		_4
	};

	//data management
	//struct Reg
	//{
		// config registers rd/wr
		struct Config : public WrRdRegisterGroup
		{
			struct
			{
				uint8_t adcopt : 1;
				uint8_t dten : 1;
				uint8_t refon : 1;
				uint8_t gpio1 : 1;
				uint8_t gpio2 : 1;
				uint8_t gpio3 : 1;
				uint8_t gpio4 : 1;
				uint8_t gpio5 : 1;
			};
			struct
			{
				//0 - 7
				uint8_t vuv_lsb;
			};
			struct
			{
				//8 - 12
				uint8_t vuv_msb : 4;
				//0 - 3
				uint8_t vov_lsb : 4;
			};
			struct
			{
				//4 - 12
				uint8_t vov_msb;
			};
			struct
			{
				uint8_t dcc1 : 1;
				uint8_t dcc2 : 1;
				uint8_t dcc3 : 1;
				uint8_t dcc4 : 1;
				uint8_t dcc5 : 1;
				uint8_t dcc6 : 1;
				uint8_t dcc7 : 1;
				uint8_t dcc8 : 1;
			};
			struct
			{
				uint8_t dcc9 : 1;
				uint8_t dcc10 : 1;
				uint8_t dcc11 : 1;
				uint8_t dcc12 : 1;
				uint8_t dcto : 4;
			};
		};
		// cell voltage rd [A:D] / [1:4]
		struct CellVoltage : public RdRegisterGroup
		{
			struct Cell
			{
				//uint8_t bytes[2];
				uint16_t val;
			} cell[3];
		};
		// gpio[0:2] voltage A  rd
		struct AuxilliaryVoltageA : public RdRegisterGroup
		{
			struct Gpio
			{
				//uint8_t bytes[2];
				uint16_t val;
			} gpio[3];
		};
		// gpio[3:4] + ref voltage A  rd
		struct AuxilliaryVoltageB : public RdRegisterGroup
		{
			struct Gpio
			{
				//uint8_t bytes[2];
				uint16_t val;
			} gpio[2];
			struct Ref
			{
				//uint8_t bytes[2];
				uint16_t val;
			} ref[2];
		};
		// status rd
		struct StatusA : public RdRegisterGroup
		{
			//uint8_t sc[2];
			uint16_t sc;
			//uint8_t itmp[2];
			uint16_t itmp;
			//uint8_t va[2];
			uint16_t va;
		};
		struct StatusB : public RdRegisterGroup
		{
			//uint8_t vd[2];
			uint16_t vd;
			struct
			{
				uint8_t c1ov : 1;
				uint8_t c1uv : 1;
				uint8_t c2ov : 1;
				uint8_t c2uv : 1;
				uint8_t c3ov : 1;
				uint8_t c3uv : 1;
				uint8_t c4ov : 1;
				uint8_t c4uv : 1;
			};
			struct
			{
				uint8_t c5ov : 1;
				uint8_t c5uv : 1;
				uint8_t c6ov : 1;
				uint8_t c6uv : 1;
				uint8_t c7ov : 1;
				uint8_t c7uv : 1;
				uint8_t c8ov : 1;
				uint8_t c8uv : 1;
			};
			struct
			{
				uint8_t c9ov : 1;
				uint8_t c9uv : 1;
				uint8_t c10ov : 1;
				uint8_t c10uv : 1;
				uint8_t c11ov : 1;
				uint8_t c11uv : 1;
				uint8_t c12ov : 1;
				uint8_t c12uv : 1;
			};
			struct
			{
				uint8_t thsd : 1;
				uint8_t muxfail : 1;
				uint8_t rsvd : 2;
				uint8_t rvs : 4;
			};
		};
		// communication rd
		struct Communication : public WrRdRegisterGroup
		{
			struct
			{
				uint8_t d0_msb : 4;
				uint8_t icom0 : 4;
			};
			struct
			{
				uint8_t fcomm0 : 4;
				uint8_t d0_lsb : 4;
			};
			struct
			{
				uint8_t d1_msb : 4;
				uint8_t icomm1 : 4;
			};
			struct
			{
				uint8_t fcomm1 : 4;
				uint8_t d1_lsb : 4;
			};
			struct
			{
				uint8_t d2_msb : 4;
				uint8_t icomm2 : 4;
			};
			struct
			{
				uint8_t fcomm2 : 4;
				uint8_t d2_lsb : 4;
			};
		};
#if LTC6804_COMPATIBLE_ONLY == 0
		// S control rd/wr
		struct SControl : public WrRdRegisterGroup
		{
			struct
			{
				uint8_t sctl1 : 4;
				uint8_t sctl2 : 4;
			};
			struct
			{
				uint8_t sctl3 : 4;
				uint8_t sctl4 : 4;
			};
			struct
			{
				uint8_t sctl5 : 4;
				uint8_t sctl6 : 4;
			};
			struct
			{
				uint8_t sctl7 : 4;
				uint8_t sctl8 : 4;
			};
			struct
			{
				uint8_t sctl9 : 4;
				uint8_t sctl10 : 4;
			};
			struct
			{
				uint8_t sctl11 : 4;
				uint8_t sctl12 : 4;
			};
		};
		// PWM rd/wr
		struct Pwm : public WrRdRegisterGroup
		{
			struct
			{
				uint8_t pwm1 : 4;
				uint8_t pwm2 : 4;
			};
			struct
			{
				uint8_t pwm3 : 4;
				uint8_t pwm4 : 4;
			};
			struct
			{
				uint8_t pwm5 : 4;
				uint8_t pwm6 : 4;
			};
			struct
			{
				uint8_t pwm7 : 4;
				uint8_t pwm8 : 4;
			};
			struct
			{
				uint8_t pwm9 : 4;
				uint8_t pwm10 : 4;
			};
			struct
			{
				uint8_t pwm11 : 4;
				uint8_t pwm12: 4;
			};
		};
#endif
	//};


	template < class Reg >
	static constexpr bool RegEq(Reg reg1, Reg reg2)
	{
		return reg1 == reg2;
	}
};

template <>
constexpr bool LTC6811::RegEq(Config cfg1, Config cfg2)
{
	if (cfg1.gpio1 		!= cfg2.gpio1) 		return false;
	if (cfg1.gpio2 		!= cfg2.gpio2) 		return false;
	if (cfg1.gpio3 		!= cfg2.gpio3) 		return false;
	if (cfg1.gpio4 		!= cfg2.gpio4) 		return false;
	if (cfg1.gpio5 		!= cfg2.gpio5) 		return false;
	if (cfg1.refon 		!= cfg2.refon) 		return false;
	if (cfg1.adcopt 	!= cfg2.adcopt) 	return false;
	if (cfg1.dcc1 		!= cfg2.dcc1) 		return false;
	if (cfg1.dcc2 		!= cfg2.dcc2) 		return false;
	if (cfg1.dcc3 		!= cfg2.dcc3) 		return false;
	if (cfg1.dcc4 		!= cfg2.dcc4) 		return false;
	if (cfg1.dcc5 		!= cfg2.dcc5) 		return false;
	if (cfg1.dcc6 		!= cfg2.dcc6) 		return false;
	if (cfg1.dcc7 		!= cfg2.dcc7) 		return false;
	if (cfg1.dcc8 		!= cfg2.dcc8) 		return false;
	if (cfg1.dcc9 		!= cfg2.dcc9) 		return false;
	if (cfg1.dcc10 		!= cfg2.dcc10) 		return false;
	if (cfg1.dcc11 		!= cfg2.dcc11)		return false;
	if (cfg1.dcc12 		!= cfg2.dcc12)		return false;
	if (cfg1.vuv_lsb 	!= cfg2.vuv_lsb) 	return false;
	if (cfg1.vuv_msb	!= cfg2.vuv_msb) 	return false;
	if (cfg1.vov_lsb 	!= cfg2.vov_lsb) 	return false;
	if (cfg1.vov_msb 	!= cfg2.vov_msb)	return false;
	if (cfg1.dcto 		!= cfg2.dcto) 		return false;
	return true;
}

#endif /* INC_PUTM_LTC_6811_LTC6804_LIB_LTC6811LIB_HPP_ */
