/*
 * ads131m04.hpp
 *
 *  Created on: Feb 12, 2025
 *      Author: lenovo
 */

#ifndef INC_ADS131M04_HPP_
#define INC_ADS131M04_HPP_

#include "main.h"

struct Id
{
private:
	const uint16_t reserved0: 8;
public:
	const uint16_t chancnt: 4;
private:
	const uint16_t reserved1: 4;
};

enum struct CrcType : uint16_t
{
	CCITT,
	ANSI
};

struct Status
{
public:
	const bool drdy0: 1;
	const bool drdy1: 1;
	const bool drdy2: 1;
	const bool drdy3: 1;
private:
	const uint16_t reserved0: 4;
public:
	const uint16_t wlength: 2;
	const bool reset: 1;
	const CrcType crc_type: 1;
	const bool crc_err: 1;
	const bool reg_map: 1;
	const bool f_resync: 1;
	const bool lock: 1;
};

struct Mode
{
public:
	bool drdy_fmt: 1;
	bool drdy_hiz: 1;
	uint16_t drdy_sel: 2;
	bool timeout: 1;
private:
	const uint16_t reserved0: 3 = { 0b000 };
public:
	uint16_t wlength: 2;
	bool reset: 1;
	CrcType crc_type: 1;
	bool rx_crc_en: 1;
	bool reg_crc_en: 1;
private:
	const uint16_t reserved1: 2 = { 0b00 };
};

enum struct Pwr : uint16_t
{
	VeryLowPower,
	LowPower,
	HighRes,
	HighRes
};

enum struct Osr
{
	_128,
	_256,
	_512,
	_1024,
	_2048,
	_4096,
	_8192,
	_16256
};

struct Clock
{
public:
	Pwr pwr: 2;
	Osr osr: 3;
	bool tbm: 1;
private:
	const uint16_t reserved0: 2 = { 0b00 };
public:
	bool ch0_en: 1;
	bool ch1_en: 1;
	bool ch2_en: 1;
	bool ch3_en: 1;
private:
	const uint16_t reserved1: 4 = { 0b0000 };
};

enum struct Gain
{
	_1,
	_2,
	_4,
	_8,
	_16,
	_32,
	_64,
	_128,
};

struct Gain1
{
public:
	Gain pga_gain0 : 3;
private:
	const uint16_t reserved0: 1 = { 0b0 };
public:
	Gain pga_gain1 : 3;
private:
	const uint16_t reserved1: 1 = { 0b0 };
public:
	Gain pga_gain2 : 3;
private:
	const uint16_t reserved2: 1 = { 0b0 };
public:
	Gain pga_gain3 : 3;
private:
	const uint16_t reserved3: 1 = { 0b0 };
};

struct Reserved
{
private:
	const uint16_t reserved0 = { 0x0000 };
};

enum struct CdLen
{
	_128,
	_256,
	_512,
	_768,
	_1280,
	_1792,
	_2560,
	_3584
};

enum struct CdNum
{
	_1,
	_2,
	_4,
	_8,
	_16,
	_32,
	_64,
	_128,
};

enum struct GcDly : uint16_t
{
	_2,
	_4,
	_8,
	_16,
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
	_32768,
	_65536
};

struct Cfg
{
public:
	bool cd_en: 1;
	CdLen cd_len: 3;
	CdNum cd_num : 3;
	bool cd_allch: 1;
	bool gc_en: 1;
	GcDly gc_dly: 4 = { 0b0011 };
private:
	const uint16_t reserved0: 3;
};

struct ThrshldMsb
{
public:
	uint16_t cd_th_msb;
};

enum struct DcBlock : uint16_t
{
	dis,
	_1_4,
	_1_8,
	_1_16,
	_1_32,
	_1_64,
	_1_128,
	_1_256,
	_1_512,
	_1_1024,
	_1_2048,
	_1_4096,
	_1_8192,
	_1_16384,
	_1_32768,
	_1_65536
};

struct ThrshldLsb
{
public:
	DcBlock dc_block : 4;
private:
	const uint16_t reserved0 : 4;
public:
	uint16_t cd_th_lsb: 8;
};

enum struct Mux : uint16_t
{
	InPM,
	AdcShorted,
	DcTestP,
	DcTestN
};

// for channels 0-3

struct ChCfg
{
public:
	Mux mux: 2;
	bool dcblk_dis: 1;
private:
	const uint16_t: 3 = { 0b000 };
public:
	uint16_t phase: 10;
};

// for channels 0-3

struct ChOcalMsb
{
public:
	uint16_t ocal_msb;
};

// for channels 0-3

struct ChOcalLsb
{
public:
	uint16_t ocal_lsb: 8;
private:
	const uint16_t reserved0: 8;
};

// for channels 0-3

struct ChGcalMsb
{
public:
	uint16_t gcal_msb;
};

// for channels 0-3

struct ChGcalLsb
{
public:
	uint16_t gcal_lsb: 8;
private:
	const uint16_t reserved0: 8;
};

struct RegMapCrc
{
public:
	uint16_t reg_crc;
};

#endif /* INC_ADS131M04_HPP_ */
