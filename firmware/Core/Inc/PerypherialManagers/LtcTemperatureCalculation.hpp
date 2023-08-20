/*
 * LtcTemperatureCalculation.hpp
 *
 *  Created on: Aug 20, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_LTCTEMPERATURECALCULATION_HPP_
#define INC_PERYPHERIALMANAGERS_LTCTEMPERATURECALCULATION_HPP_


// ltc reading to temperature
constexpr static int16_t temperature_map[29][2] = {
		//		ltc value ,  temperature *C
		{27190	,	-20} ,
		{26380	,	-15} ,
		{25400	,	-10} ,
		{24260	,	-5}	,
		{22960	,	0}	,
		{21520	,	5}	,
		{19960	,	10}	,
		{18330	,	15}	,
		{16660	,	20}	,
		{15000	,	25}	,
		{13380	,	30}	,
		{11850	,	35}	,
		{10420	,	40}	,
		{9120	,	45}	,
		{7940	,	50}	,
		{6890	,	55}	,
		{5970	,	60}	,
		{5170	,	65}	,
		{4470	,	70}	,
		{3860	,	75}	,
		{3350	,	80}	,
		{2900	,	85}	,
		{2520	,	90}	,
		{2190	,	95}	,
		{1910	,	100} ,
		{1660	,	105} ,
		{1450	,	110} ,
		{1270	,	115}
};


/**
 * Brief:	Calculation of temperature, from value of measured voltage
 * Param:	ltc_value:	Value of voltage, LSB -> 0.1 mV
 * Retval:	Temperature in 0.1*C, integer
 */
constexpr float LtcCalculateTemperature(uint16_t gpio_voltage)
{
	if (gpio_voltage > INT16_MAX) gpio_voltage = INT16_MAX;
	float result = 0.0;
	for(int i = 1; i < 28; i++)
	{
		if(gpio_voltage >= temperature_map[i][0])
		{
			// approximation
			result = (float)(temperature_map[i][1])
									-
									5.0 * ((float)gpio_voltage-(float)(temperature_map[i][0]))
									/
									((float)(temperature_map[i-1][0]) - (float)(temperature_map[i][0]));
			break;
		}
	}

	return (result);
}



#endif /* INC_PERYPHERIALMANAGERS_LTCTEMPERATURECALCULATION_HPP_ */
