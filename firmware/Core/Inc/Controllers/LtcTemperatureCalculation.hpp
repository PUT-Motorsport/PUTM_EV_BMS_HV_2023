/*
 * LtcTemperatureCalculation.hpp
 *
 *  Created on: Aug 20, 2023
 *      Author: jan
 */

#ifndef INC_CONTROLLERS_LTCTEMPERATURECALCULATION_HPP_
#define INC_CONTROLLERS_LTCTEMPERATURECALCULATION_HPP_


// ltc reading to temperature
constexpr static float temperature_map[29][2] =
{
	// ltc value ,  temperature *C
	{ 	2.7190f	,	-20.f	},
	{ 	2.6380f	,	-15.f	},
	{ 	2.5400f	,	-10.f	},
	{ 	2.4260f	,	-5.f	},
	{ 	2.2960f	,	0.f		},
	{ 	2.1520f	,	5.f		},
	{ 	1.9960f	,	10.f	},
	{ 	1.8330f	,	15.f	},
	{ 	1.6660f	,	20.f	},
	{ 	1.5000f	,	25.f	},
	{ 	1.3380f	,	30.f	},
	{ 	1.1850f	,	35.f	},
	{ 	1.0420f	,	40.f	},
	{ 	0.9120f	,	45.f	},
	{ 	0.7940f	,	50.f	},
	{ 	0.6890f	,	55.f	},
	{ 	0.5970f	,	60.f	},
	{	0.5170f	,	65.f	},
	{ 	0.4470f	,	70.f	},
	{ 	0.3860f	,	75.f	},
	{ 	0.3350f	,	80.f	},
	{ 	0.2900f	,	85.f	},
	{ 	0.2520f	,	90.f	},
	{ 	0.2190f	,	95.f	},
	{ 	0.1910f	,	100.f	},
	{ 	0.1660f	,	105.f	},
	{ 	0.1450f	,	110.f	},
	{ 	0.1270f	,	115.f	}
};


/**
 * Brief:	Calculation of temperature, from value of measured voltage
 * Param:	ltc_value:	Value of voltage, LSB -> 0.1 mV
 * Retval:	Temperature in 0.1*C, integer
 */
constexpr float ltcCalculateTemperature(float gpio_voltage)
{
	//if (gpio_voltage > INT16_MAX) gpio_voltage = INT16_MAX;
	float result = 0.0;
	for(int i = 1; i < 28; i++)
	{
		if(gpio_voltage >= temperature_map[i][0])
		{
			// approximation
			result 	= (float)(temperature_map[i][1])
					-
					5.0 * ((float)gpio_voltage-(float)(temperature_map[i][0]))
					/
					((float)(temperature_map[i-1][0]) - (float)(temperature_map[i][0]));
			break;
		}
	}

	return (result);
}



#endif /* INC_CONTROLLERS_LTCTEMPERATURECALCULATION_HPP_ */
