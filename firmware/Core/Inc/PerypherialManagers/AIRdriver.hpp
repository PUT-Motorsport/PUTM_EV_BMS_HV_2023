/*
 * AIRdriver.hpp
 *
 *  Created on: Aug 15, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_AIRDRIVER_HPP_
#define INC_PERYPHERIALMANAGERS_AIRDRIVER_HPP_


#include "PerypherialManagers/GpioController.hpp"
#include "AirSM.hpp"
#include "main.h"

class AIRdriver
{
	inline static GpioOut air_p { SIG_AIR_P_GPIO_Port, SIG_AIR_P_Pin, false };
	inline static GpioOut air_m { SIG_AIR_M_GPIO_Port, SIG_AIR_M_Pin, false };
	inline static GpioOut air_pre { SIG_AIR_PRE_GPIO_Port, SIG_AIR_PRE_Pin, false };

public:
	inline static void SetState(AIRstateEnum state){
		switch (state) {
			case AIRstateEnum::Open:
				air_m.deactivate();
				air_p.deactivate();
				air_pre.deactivate();
				break;

			case AIRstateEnum::Precharge:
				air_m.activate();
				air_p.deactivate();
				air_pre.activate();
				break;

			case AIRstateEnum::Closed:
				air_m.activate();
				air_p.activate();
				air_pre.deactivate();
				break;
		}
	}

};



#endif /* INC_PERYPHERIALMANAGERS_AIRDRIVER_HPP_ */
